import os
import shutil
import tkinter as tk
from tkinter import messagebox, filedialog, ttk
from PIL import Image, ImageTk

from views.perfume_card import PerfumeCard


class PerfumeController:

    def __init__(self, repository, perfumery_repository, inventory_repository, view):

        self.repository = repository
        self.perfumery_repository = perfumery_repository
        self.inventory_repository = inventory_repository
        self.view = view

        self.repository.add_observer(self)
        self.perfumery_repository.add_observer(self)
        self.inventory_repository.add_observer(self)

        self.view._lang_service.add_listener(self)

        self._setup_view()

        self.refresh_view()

    def on_language_changed(self, language_code):

        self.update_translations()

    def _setup_view(self):

        self.view.add_button.config(command=self.handle_add)
        self.view.update_button.config(command=self.handle_update)
        self.view.delete_button.config(command=self.handle_delete)
        self.view.clear_button.config(command=self.handle_clear)
        self.view.browse_button.config(command=self.handle_browse_image)

        self.view.search_button.config(command=self.handle_search)
        self.view.filter_brand_combo.bind("<<ComboboxSelected>>", lambda e: self.handle_filter())
        self.view.sort_button.config(command=self.handle_sort)

        self.view.cards_container.bind("<Configure>", self.handle_cards_container_configure)
        self.view.canvas.bind("<Configure>", self.handle_canvas_configure)
        self.view.canvas.bind_all("<MouseWheel>", self.handle_mousewheel)

        self.view.form_canvas.bind_all("<MouseWheel>", self.handle_form_mousewheel)
        self.view.canvas.bind_all("<MouseWheel>", self.handle_cards_mousewheel)

        self.view.cards_container.bind("<Configure>", self.handle_cards_container_configure)
        self.view.canvas.bind("<Configure>", self.handle_canvas_configure)

        self.update_translations()

    def handle_form_mousewheel(self, event):

        self.view.form_canvas.yview_scroll(int(-1 * (event.delta / 120)), "units")

    def handle_cards_mousewheel(self, event):

        self.view.canvas.yview_scroll(int(-1 * (event.delta / 120)), "units")

    def handle_cards_container_configure(self, event):

        self.view.canvas.configure(scrollregion=self.view.canvas.bbox("all"))

    def handle_canvas_configure(self, event):

        self.view.canvas.itemconfig(self.view.canvas_window, width=event.width)

    def update_perfumeries_for_perfume(self, perfume_id):

        for item in self.view.perfumeries_table.get_children():
            self.view.perfumeries_table.delete(item)

        inventory_items = self.inventory_repository.get_all_by_perfume(perfume_id)

        if not inventory_items:
            self.view.perfumeries_table.insert('', 'end', values=('',
                                                                  self.view._lang_service.get_text("no_inventory"),
                                                                  '', ''))
            return

        for item in inventory_items:

            perfumery = self.perfumery_repository.get_by_id(item.perfumery_id)
            if perfumery:
                availability_text = self.view._lang_service.get_text(
                    "available") if item.is_available else self.view._lang_service.get_text("out_of_stock")

                values = (
                    perfumery.id,
                    perfumery.name,
                    perfumery.city,
                    f"{item.quantity} ({availability_text})"
                )
                self.view.perfumeries_table.insert('', 'end', values=values)

    def handle_cards_container_configure(self, event):

        self.view.canvas.configure(scrollregion=self.view.canvas.bbox("all"))

    def handle_canvas_configure(self, event):

        self.view.canvas.itemconfig(self.view.canvas.find_withtag("all")[0], width=event.width)

    def handle_mousewheel(self, event):

        self.view.canvas.yview_scroll(int(-1 * (event.delta / 120)), "units")

    def handle_add(self):

        form_data = self.get_form_data_from_view()

        if not form_data["name"] or not form_data["brand"] or form_data["price"] <= 0:
            self.show_error("fill_required")
            return

        if form_data["image_path"] and os.path.exists(form_data["image_path"]) and not form_data[
            "image_path"].startswith("images/perfumes"):
            form_data["image_path"] = self._save_image_file(form_data["image_path"])

        self.repository.create(
            name=form_data["name"],
            brand=form_data["brand"],
            price=form_data["price"],
            description=form_data["description"],
            volume_ml=form_data["volume_ml"],
            concentration=form_data["concentration"],
            gender=form_data["gender"],
            image_path=form_data["image_path"]
        )

        self.clear_form()

    def handle_update(self):

        perfume_id = self.view._current_perfume_id
        if not perfume_id:
            return

        form_data = self.get_form_data_from_view()

        if not form_data["name"] or not form_data["brand"] or form_data["price"] <= 0:
            self.show_error("fill_required")
            return

        if form_data["image_path"] and os.path.exists(form_data["image_path"]) and not form_data[
            "image_path"].startswith("images/perfumes"):
            form_data["image_path"] = self._save_image_file(form_data["image_path"])

        self.repository.update(perfume_id, **form_data)

    def handle_delete(self):

        perfume_id = self.view._current_perfume_id
        if not perfume_id:
            return

        if self.confirm_delete():
            self.repository.delete(perfume_id)

            self.clear_form()

    def handle_clear(self):

        self.clear_form()

    def handle_browse_image(self):

        file_path = filedialog.askopenfilename(
            title=self.view._lang_service.get_text("browse"),
            filetypes=[
                ("Image Files", "*.png *.jpg *.jpeg *.gif"),
                ("All Files", "*.*")
            ]
        )

        if file_path:
            filename = os.path.basename(file_path)
            self.view.image_var.set(filename)

            self.update_image_preview(file_path)

    def handle_search(self):

        search_term = self.view.search_var.get().strip()
        if search_term:
            perfumes = self.repository.search_by_name(search_term)
        else:
            perfumes = self.repository.get_all()

        self.update_perfumes_list(perfumes)

    def handle_filter(self):

        brand = self.view.filter_brand_var.get()
        if brand == self.view._lang_service.get_text("all_brands"):
            brand = ""

        if brand:
            perfumes = self.repository.filter_by_brand(brand)
        else:
            perfumes = self.repository.get_all()

        self.update_perfumes_list(perfumes)

    def handle_sort(self):

        sort_by = self.view.sort_var.get().lower()
        sort_desc = self.view.sort_desc_var.get()

        perfumes = self.repository.get_all(sort_by=sort_by, sort_desc=sort_desc)
        self.update_perfumes_list(perfumes)

    def handle_card_selection(self, perfume_id):

        self.select_perfume(perfume_id)

    def update(self, observable, *args, **kwargs):

        if observable != self.repository:
            return

        if len(args) > 0:
            event_type = args[0]

            if event_type == "create":

                self.update_perfumes_list(observable.get_all())
                self.update_brands_filter(observable.get_all_brands())

                self.show_message("add_success")

            elif event_type == "update":

                self.update_perfumes_list(observable.get_all())
                self.update_brands_filter(observable.get_all_brands())

                self.show_message("update_success")

            elif event_type == "delete":

                self.update_perfumes_list(observable.get_all())
                self.update_brands_filter(observable.get_all_brands())

                self.show_message("delete_success")

    def refresh_view(self):

        perfumes = self.repository.get_all()
        self.update_perfumes_list(perfumes)

        brands = self.repository.get_all_brands()
        self.update_brands_filter(brands)

    def update_perfumes_list(self, perfumes):

        self.view._perfumes = perfumes

        for widget in self.view.cards_container.winfo_children():
            widget.destroy()

        if not perfumes:
            no_results = tk.Label(self.view.cards_container,
                                  text=self.view._lang_service.get_text("no_results"),
                                  font=("", 12), padx=20, pady=20)
            no_results.pack(pady=50)
            return

        canvas_width = self.view.canvas.winfo_width()
        cards_per_row = max(1, canvas_width // 220)

        row, col = 0, 0
        self.view.perfume_cards = []

        for perfume in perfumes:

            card = self.create_perfume_card(perfume, row, col)
            self.view.perfume_cards.append(card)

            col += 1
            if col >= cards_per_row:
                col = 0
                row += 1

    def create_perfume_card(self, perfume, row, col):

        card = PerfumeCard(self.view.cards_container, perfume,
                           lang_service=self.view._lang_service,
                           padding=5)
        card.grid(row=row, column=col, padx=10, pady=10, sticky="nw")

        card.bind("<Button-1>", lambda e, p=perfume: self.handle_card_selection(p.id))

        for child in card.winfo_children():
            child.bind("<Button-1>", lambda e, p=perfume: self.handle_card_selection(p.id))

            for subchild in child.winfo_children():
                subchild.bind("<Button-1>", lambda e, p=perfume: self.handle_card_selection(p.id))

        return card

    def update_brands_filter(self, brands):

        current_brand = self.view.filter_brand_var.get()

        self.view.filter_brand_combo['values'] = [self.view._lang_service.get_text("all_brands")] + brands

        if current_brand and current_brand != self.view._lang_service.get_text(
                "all_brands") and current_brand in brands:
            self.view.filter_brand_var.set(current_brand)
        else:
            self.view.filter_brand_var.set(self.view._lang_service.get_text("all_brands"))

    def clear_form(self):

        self.view._current_perfume_id = None
        self.view.name_var.set("")
        self.view.brand_var.set("")
        self.view.price_var.set(0)
        self.view.description_text.delete("1.0", "end")
        self.view.volume_var.set(0)
        self.view.concentration_var.set("")
        self.view.gender_var.set("")
        self.view.image_var.set("")

        self.view.image_preview.configure(image=None, text="")

        if hasattr(self.view, 'perfume_cards'):
            for card in self.view.perfume_cards:
                self.deselect_card(card)

    def select_perfume(self, perfume_id):

        for card in self.view.perfume_cards:
            if card.perfume.id == perfume_id:
                self.select_card(card)
            else:
                self.deselect_card(card)

        selected_perfume = None
        for perfume in self.view._perfumes:
            if perfume.id == perfume_id:
                selected_perfume = perfume
                break

        if selected_perfume:

            self.view._current_perfume_id = selected_perfume.id
            self.view.name_var.set(selected_perfume.name)
            self.view.brand_var.set(selected_perfume.brand)
            self.view.price_var.set(selected_perfume.price)
            self.view.description_text.delete("1.0", "end")
            self.view.description_text.insert("1.0", selected_perfume.description or "")
            self.view.volume_var.set(selected_perfume.volume_ml or 0)

            if selected_perfume.concentration:

                if selected_perfume.concentration == "Eau de Cologne":
                    self.view.concentration_var.set(self.view._lang_service.get_text("edc"))
                elif selected_perfume.concentration == "Eau de Toilette":
                    self.view.concentration_var.set(self.view._lang_service.get_text("edt"))
                elif selected_perfume.concentration == "Eau de Parfum":
                    self.view.concentration_var.set(self.view._lang_service.get_text("edp"))
                elif selected_perfume.concentration == "Parfum":
                    self.view.concentration_var.set(self.view._lang_service.get_text("parfum"))
                else:
                    self.view.concentration_var.set(selected_perfume.concentration)
            else:
                self.view.concentration_var.set("")

            if selected_perfume.gender:

                if selected_perfume.gender == "Male":
                    self.view.gender_var.set(self.view._lang_service.get_text("male"))
                elif selected_perfume.gender == "Female":
                    self.view.gender_var.set(self.view._lang_service.get_text("female"))
                elif selected_perfume.gender == "Unisex":
                    self.view.gender_var.set(self.view._lang_service.get_text("unisex"))
                else:
                    self.view.gender_var.set(selected_perfume.gender)
            else:
                self.view.gender_var.set("")

            self.view.image_var.set(selected_perfume.image_path or "")

            if selected_perfume.image_path:
                image_path = os.path.join("images/perfumes", selected_perfume.image_path)
                self.update_image_preview(image_path)
            else:
                self.view.image_preview.configure(image=None, text="")

        self.update_perfumeries_for_perfume(perfume_id)

    def select_card(self, card):

        card.selected = True
        card.configure(relief=tk.SUNKEN, borderwidth=2)

    def deselect_card(self, card):

        card.selected = False
        card.configure(relief=tk.RAISED, borderwidth=1)

    def update_image_preview(self, file_path):

        try:
            if file_path and os.path.exists(file_path):

                image = Image.open(file_path)

                image = image.resize((190, 190), Image.LANCZOS)

                photo = ImageTk.PhotoImage(image)

                self.view.image_preview.configure(image=photo)
                self.view.image_preview.image = photo
            else:
                self.view.image_preview.configure(image=None, text="No Image")
        except Exception as e:
            print(f"Error updating image preview: {e}")
            self.view.image_preview.configure(image=None, text="Error")

    def get_form_data_from_view(self):

        return {
            "name": self.view.name_var.get().strip(),
            "brand": self.view.brand_var.get().strip(),
            "price": self.view.price_var.get(),
            "description": self.view.description_text.get("1.0", "end-1c").strip(),
            "volume_ml": self.view.volume_var.get() if self.view.volume_var.get() > 0 else None,
            "concentration": self.view.concentration_var.get(),
            "gender": self.view.gender_var.get(),
            "image_path": self.view.image_var.get().strip()
        }

    def show_message(self, message_key):

        message = self.view._lang_service.get_text(message_key)
        self.view.show_message(message)

    def show_error(self, message_key):

        message = self.view._lang_service.get_text(message_key)
        messagebox.showerror(self.view._lang_service.get_text("error"), message)

    def confirm_delete(self):

        return messagebox.askyesno(
            self.view._lang_service.get_text("confirm_delete"),
            self.view._lang_service.get_text("confirm_delete_msg")
        )

    def _save_image_file(self, image_path):

        if not image_path:
            return None

        try:

            filename = os.path.basename(image_path)

            images_dir = "images/perfumes"
            os.makedirs(images_dir, exist_ok=True)

            dest_path = os.path.join(images_dir, filename)

            if os.path.abspath(image_path) == os.path.abspath(dest_path):
                return filename

            if os.path.exists(image_path):
                print(f"Copying image from {image_path} to {dest_path}")
                shutil.copy2(image_path, dest_path)
                return filename
            else:
                print(f"Source image does not exist: {image_path}")
                return None
        except Exception as e:
            print(f"Error saving image: {e}")
            return None

    def update_card_translations(self, card):

        if not card.lang_service:
            return

        if card.perfume.gender:
            gender_key = card.perfume.gender.lower()
            if gender_key in ["male", "female", "unisex"]:
                translated = card.lang_service.get_text(gender_key)

                info_parts = []
                if card.perfume.concentration:

                    conc = card.perfume.concentration
                    if conc == "Eau de Cologne":
                        conc = card.lang_service.get_text("edc")
                    elif conc == "Eau de Toilette":
                        conc = card.lang_service.get_text("edt")
                    elif conc == "Eau de Parfum":
                        conc = card.lang_service.get_text("edp")
                    elif conc == "Parfum":
                        conc = card.lang_service.get_text("parfum")
                    info_parts.append(conc)

                if card.perfume.volume_ml:
                    info_parts.append(f"{card.perfume.volume_ml} ml")

                info_parts.append(translated)

                info_text = " • ".join(info_parts)
                card.info_label.configure(text=info_text)

    def update_translations(self):

        self.view.name_label.configure(text=self.view._lang_service.get_text("name"))
        self.view.brand_label.configure(text=self.view._lang_service.get_text("brand"))
        self.view.price_label.configure(text=self.view._lang_service.get_text("price"))
        self.view.desc_label.configure(text=self.view._lang_service.get_text("description"))
        self.view.volume_label.configure(text=self.view._lang_service.get_text("volume"))
        self.view.conc_label.configure(text=self.view._lang_service.get_text("concentration"))
        self.view.gender_label.configure(text=self.view._lang_service.get_text("gender"))
        self.view.image_label.configure(text=self.view._lang_service.get_text("image"))
        self.view.preview_label.configure(text=self.view._lang_service.get_text("preview"))

        self.view.add_button.configure(text=self.view._lang_service.get_text("add"))
        self.view.update_button.configure(text=self.view._lang_service.get_text("update"))
        self.view.delete_button.configure(text=self.view._lang_service.get_text("delete"))
        self.view.clear_button.configure(text=self.view._lang_service.get_text("clear"))
        self.view.browse_button.configure(text=self.view._lang_service.get_text("browse"))

        self.view.search_label.configure(text=self.view._lang_service.get_text("search"))
        self.view.search_button.configure(text=self.view._lang_service.get_text("search"))
        self.view.filter_label.configure(text=self.view._lang_service.get_text("filter_brand"))
        self.view.sort_label.configure(text=self.view._lang_service.get_text("sort_by"))
        self.view.sort_desc_check.configure(text=self.view._lang_service.get_text("descending"))
        self.view.sort_button.configure(text=self.view._lang_service.get_text("sort"))

        self.view.perfumeries_label.configure(text=self.view._lang_service.get_text("available_at"))
        self.view.perfumeries_table.heading('name', text=self.view._lang_service.get_text("name").replace(":", ""))
        self.view.perfumeries_table.heading('city', text=self.view._lang_service.get_text("city").replace(":", ""))
        self.view.perfumeries_table.heading('quantity',
                                            text=self.view._lang_service.get_text("quantity_availability").replace(":",
                                                                                                                   ""))

        self.view.concentration_combo['values'] = [
            "",
            self.view._lang_service.get_text("edc"),
            self.view._lang_service.get_text("edt"),
            self.view._lang_service.get_text("edp"),
            self.view._lang_service.get_text("parfum")
        ]

        self.view.gender_combo['values'] = [
            "",
            self.view._lang_service.get_text("male"),
            self.view._lang_service.get_text("female"),
            self.view._lang_service.get_text("unisex")
        ]

        current_selection = self.view.filter_brand_var.get()
        current_values = list(self.view.filter_brand_combo['values'])

        if len(current_values) > 0:
            current_values[0] = self.view._lang_service.get_text("all_brands")
            self.view.filter_brand_combo['values'] = current_values

            if current_selection and current_selection != self.view._lang_service.get_text("all_brands"):
                self.view.filter_brand_var.set(current_selection)
            else:
                self.view.filter_brand_var.set(self.view._lang_service.get_text("all_brands"))

        for child in self.view.winfo_children():
            if isinstance(child, ttk.LabelFrame):
                child.configure(text=self.view._lang_service.get_text("details"))

        if hasattr(self.view, 'perfume_cards'):
            for card in self.view.perfume_cards:
                self.update_card_translations(card)
