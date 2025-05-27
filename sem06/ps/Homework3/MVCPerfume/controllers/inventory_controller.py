from tkinter import messagebox, ttk


class InventoryController:

    def __init__(self, perfumery_repository, perfume_repository, inventory_repository, view):

        self.perfumery_repository = perfumery_repository
        self.perfume_repository = perfume_repository
        self.inventory_repository = inventory_repository
        self.view = view

        self.perfumery_name_to_id = {}
        self.perfumery_id_to_name = {}
        self.perfume_option_to_id = {}

        self.inventory_repository.add_observer(self)

        self.view._lang_service.add_listener(self)

        self.perfumery_repository.add_observer(self)

        self._setup_view()

        self.refresh_view()

    def _setup_view(self):

        self.view.add_inventory_button.config(command=self.handle_add_inventory)
        self.view.update_inventory_button.config(command=self.handle_update_inventory)
        self.view.delete_inventory_button.config(command=self.handle_delete_inventory)
        self.view.clear_inventory_button.config(command=self.handle_clear_inventory)

        self.view.apply_filter_button.config(command=self.handle_filter_inventory)
        self.view.filter_inv_perfumery_combo.bind("<<ComboboxSelected>>", lambda e: self.handle_filter_inventory())
        self.view.filter_availability_combo.bind("<<ComboboxSelected>>", lambda e: self.handle_filter_inventory())

        self.view.inv_perfumery_combo.bind("<<ComboboxSelected>>", lambda e: self.update_perfumes_for_perfumery())

        self.view.inventory_table.bind("<<TreeviewSelect>>", lambda e: self.handle_inventory_selection())

        self.update_translations()

    def refresh_view(self):

        perfumeries = self.perfumery_repository.get_all()

        perfumes = self.perfume_repository.get_all()

        self.update_perfumery_combos(perfumeries)

        inventory_items = self.inventory_repository.get_all()
        self.update_inventory_list(inventory_items)

    def update_perfumery_combos(self, perfumeries):

        current_perfumery = self.view.inv_perfumery_var.get()
        all_perfumeries_text = self.view._lang_service.get_text("all_perfumeries")

        perfumery_names = [(str(p.id), p.name) for p in perfumeries]

        self.view.inv_perfumery_combo['values'] = [p[1] for p in perfumery_names]

        self.view.filter_inv_perfumery_combo['values'] = [all_perfumeries_text] + [p[1] for p in perfumery_names]

        self.perfumery_name_to_id = {p[1]: p[0] for p in perfumery_names}
        self.perfumery_id_to_name = {p[0]: p[1] for p in perfumery_names}

        if current_perfumery and current_perfumery in self.perfumery_name_to_id:
            self.view.inv_perfumery_var.set(current_perfumery)
        else:
            self.view.inv_perfumery_var.set("")

        current_filter = self.view.filter_inv_perfumery_var.get()
        if current_filter and current_filter != all_perfumeries_text and current_filter in self.perfumery_name_to_id:
            self.view.filter_inv_perfumery_var.set(current_filter)
        else:
            self.view.filter_inv_perfumery_var.set(all_perfumeries_text)

    def update_perfumes_for_perfumery(self):

        perfumery_name = self.view.inv_perfumery_var.get()

        self.perfume_option_to_id = {}

        if not perfumery_name or perfumery_name not in self.perfumery_name_to_id:
            self.view.inv_perfume_combo['values'] = []
            self.view.inv_perfume_var.set("")
            return

        perfumery_id = int(self.perfumery_name_to_id[perfumery_name])

        inventory_items = self.inventory_repository.get_all_by_perfumery(perfumery_id)
        existing_perfume_ids = [item.perfume_id for item in inventory_items]

        perfumes = self.perfume_repository.get_all()

        available_perfumes = [p for p in perfumes if p.id not in existing_perfume_ids]

        perfume_options = [(str(p.id), f"{p.name} ({p.brand})") for p in available_perfumes]

        self.view.inv_perfume_combo['values'] = [p[1] for p in perfume_options]

        self.perfume_option_to_id = {p[1]: p[0] for p in perfume_options}

        self.view.inv_perfume_var.set("")

    def update_inventory_list(self, inventory_items):

        for item in self.view.inventory_table.get_children():
            self.view.inventory_table.delete(item)

        if not inventory_items:
            self.view.inventory_table.insert('', 'end', values=('',
                                                                self.view._lang_service.get_text("no_inventory_items"),
                                                                '', '', '', ''))
            return

        for item in inventory_items:

            perfumery = self.perfumery_repository.get_by_id(item.perfumery_id)
            perfume = self.perfume_repository.get_by_id(item.perfume_id)

            if perfumery and perfume:
                availability_text = self.view._lang_service.get_text(
                    "available") if item.is_available else self.view._lang_service.get_text("out_of_stock")

                values = (
                    item.id,
                    perfumery.name,
                    perfume.name,
                    perfume.brand,
                    item.quantity,
                    availability_text
                )
                self.view.inventory_table.insert('', 'end', values=values)

    def handle_inventory_selection(self):

        selected_items = self.view.inventory_table.selection()
        if not selected_items:
            return

        item_values = self.view.inventory_table.item(selected_items[0], 'values')
        inventory_id = int(item_values[0])

        inventory_item = self.inventory_repository.get_by_id(inventory_id)

        if inventory_item:

            self.view._current_inventory_id = inventory_id

            perfumery = self.perfumery_repository.get_by_id(inventory_item.perfumery_id)
            if perfumery and perfumery.name in self.perfumery_name_to_id:
                self.view.inv_perfumery_var.set(perfumery.name)

                perfume = self.perfume_repository.get_by_id(inventory_item.perfume_id)
                if perfume:
                    option = f"{perfume.name} ({perfume.brand})"

                    current_options = list(self.view.inv_perfume_combo['values'])
                    if option not in current_options:
                        current_options.append(option)
                        self.view.inv_perfume_combo['values'] = current_options
                        self.perfume_option_to_id[option] = str(perfume.id)

                    self.view.inv_perfume_var.set(option)

            self.view.inv_quantity_var.set(inventory_item.quantity)

    def handle_add_inventory(self):

        perfumery_name = self.view.inv_perfumery_var.get()
        perfume_option = self.view.inv_perfume_var.get()
        quantity = self.view.inv_quantity_var.get()

        is_available = quantity > 0

        if not perfumery_name or not perfume_option:
            self.show_error("fill_required_inventory")
            return

        if perfumery_name not in self.perfumery_name_to_id or perfume_option not in self.perfume_option_to_id:
            return

        perfumery_id = int(self.perfumery_name_to_id[perfumery_name])
        perfume_id = int(self.perfume_option_to_id[perfume_option])

        existing = self.inventory_repository.get_by_perfumery_and_perfume(perfumery_id, perfume_id)
        if existing:
            self.show_error("inventory_already_exists")
            return

        self.inventory_repository.create(
            perfumery_id=perfumery_id,
            perfume_id=perfume_id,
            quantity=quantity,
            is_available=is_available
        )

        self.handle_clear_inventory()

    def handle_update_inventory(self):

        if not self.view._current_inventory_id:
            return

        quantity = self.view.inv_quantity_var.get()

        is_available = quantity > 0

        self.inventory_repository.update(
            self.view._current_inventory_id,
            quantity=quantity,
            is_available=is_available
        )

    def handle_delete_inventory(self):

        if not self.view._current_inventory_id:
            return

        if not self.confirm_delete("confirm_delete_inventory", "confirm_delete_inventory_msg"):
            return

        self.inventory_repository.delete(self.view._current_inventory_id)

        self.handle_clear_inventory()

    def handle_clear_inventory(self):

        self.view._current_inventory_id = None
        self.view.inv_perfumery_var.set("")
        self.view.inv_perfume_var.set("")
        self.view.inv_quantity_var.set(0)

        for item in self.view.inventory_table.selection():
            self.view.inventory_table.selection_remove(item)

    def handle_filter_inventory(self):

        perfumery_name = self.view.filter_inv_perfumery_var.get()
        availability = self.view.filter_availability_var.get()

        all_perfumeries_text = self.view._lang_service.get_text("all_perfumeries")

        inventory_items = []

        if perfumery_name != all_perfumeries_text and perfumery_name in self.perfumery_name_to_id:
            perfumery_id = int(self.perfumery_name_to_id[perfumery_name])
            inventory_items = self.inventory_repository.get_all_by_perfumery(perfumery_id)
        else:
            inventory_items = self.inventory_repository.get_all()

        if availability == self.view._lang_service.get_text("available_only"):
            inventory_items = [item for item in inventory_items if item.is_available]
        elif availability == self.view._lang_service.get_text("out_of_stock_only"):
            inventory_items = [item for item in inventory_items if not item.is_available]

        self.update_inventory_list(inventory_items)

    #

    #

    #

    #

    #

    #

    def on_language_changed(self, language_code):

        self.update_translations()

    def update_translations(self):

        self.view.inv_perfumery_label.configure(text=self.view._lang_service.get_text("perfumery"))
        self.view.inv_perfume_label.configure(text=self.view._lang_service.get_text("perfume"))
        self.view.inv_quantity_label.configure(text=self.view._lang_service.get_text("quantity"))

        self.view.add_inventory_button.configure(text=self.view._lang_service.get_text("add"))
        self.view.update_inventory_button.configure(text=self.view._lang_service.get_text("update"))
        self.view.delete_inventory_button.configure(text=self.view._lang_service.get_text("delete"))
        self.view.clear_inventory_button.configure(text=self.view._lang_service.get_text("clear"))

        self.view.filter_inv_perfumery_label.configure(text=self.view._lang_service.get_text("perfumery"))
        self.view.filter_availability_label.configure(text=self.view._lang_service.get_text("show"))
        self.view.apply_filter_button.configure(text=self.view._lang_service.get_text("apply_filter"))

        self.view.filter_availability_combo['values'] = [
            self.view._lang_service.get_text("all_items"),
            self.view._lang_service.get_text("available_only"),
            self.view._lang_service.get_text("out_of_stock_only")
        ]

        perfumeries = self.perfumery_repository.get_all()
        self.update_perfumery_combos(perfumeries)

        self.view.inventory_table.heading('perfumery', text=self.view._lang_service.get_text("perfumery"))
        self.view.inventory_table.heading('perfume', text=self.view._lang_service.get_text("perfume"))
        self.view.inventory_table.heading('brand', text=self.view._lang_service.get_text("brand"))
        self.view.inventory_table.heading('quantity', text=self.view._lang_service.get_text("quantity"))
        self.view.inventory_table.heading('available', text=self.view._lang_service.get_text("available"))

        for child in self.view.winfo_children():
            if isinstance(child, ttk.Frame):
                for grandchild in child.winfo_children():
                    if isinstance(grandchild, ttk.PanedWindow):
                        for pane in grandchild.panes():
                            widget = grandchild.nametowidget(pane)
                            if isinstance(widget, ttk.LabelFrame):
                                widget.configure(text=self.view._lang_service.get_text("inventory_details"))

    def show_message(self, message_key):

        message = self.view._lang_service.get_text(message_key)
        self.view.show_message(message)

    def show_error(self, message_key):

        message = self.view._lang_service.get_text(message_key)
        messagebox.showerror(self.view._lang_service.get_text("error"), message)

    def confirm_delete(self, title_key, message_key):

        return messagebox.askyesno(
            self.view._lang_service.get_text(title_key),
            self.view._lang_service.get_text(message_key)
        )

    def update(self, observable, *args, **kwargs):

        if observable == self.inventory_repository:
            if len(args) > 0:
                event_type = args[0]
                if event_type in ["create", "update", "delete"]:
                    inventory_items = self.inventory_repository.get_all()
                    self.update_inventory_list(inventory_items)
                    message_key = f"{event_type}_inventory_success"
                    self.show_message(message_key)
                    if self.view.inv_perfumery_var.get():
                        self.update_perfumes_for_perfumery()


        elif observable == self.perfumery_repository:
            if len(args) > 0:
                event_type = args[0]
                if event_type in ["create", "update", "delete"]:

                    perfumeries = self.perfumery_repository.get_all()
                    self.update_perfumery_combos(perfumeries)

                    if event_type == "delete":
                        self.handle_filter_inventory()
