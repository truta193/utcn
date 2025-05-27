import tkinter as tk
from tkinter import ttk
from views.base_view import BaseView


class PerfumeView(BaseView):

    def __init__(self, parent):
        super().__init__(parent)

        self._current_perfume_id = None
        self._perfumes = []
        self._image_cache = {}

        self._init_ui()

    def _init_ui(self):
        main_frame = ttk.Frame(self, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        paned = ttk.PanedWindow(main_frame, orient=tk.HORIZONTAL)
        paned.pack(fill=tk.BOTH, expand=True)

        form_outer_frame = ttk.Frame(paned)

        self.form_canvas = tk.Canvas(form_outer_frame, borderwidth=0, highlightthickness=0)
        form_scrollbar = ttk.Scrollbar(form_outer_frame, orient="vertical", command=self.form_canvas.yview)
        self.form_canvas.configure(yscrollcommand=form_scrollbar.set)

        form_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.form_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        form_frame = ttk.LabelFrame(self.form_canvas, text=self._lang_service.get_text("details"), padding=10)
        self.form_window = self.form_canvas.create_window((0, 0), window=form_frame, anchor="nw")

        def _on_form_canvas_configure(event):
            self.form_canvas.configure(scrollregion=self.form_canvas.bbox("all"))

            self.form_canvas.itemconfig(self.form_window, width=event.width)

        self.form_canvas.bind("<Configure>", _on_form_canvas_configure)
        form_frame.bind("<Configure>", lambda e: self.form_canvas.configure(scrollregion=self.form_canvas.bbox("all")))

        form_grid = ttk.Frame(form_frame)
        form_grid.pack(fill=tk.BOTH, expand=True)

        row = 0

        self.name_label = ttk.Label(form_grid, text=self._lang_service.get_text("name"))
        self.name_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.name_var = tk.StringVar()
        self.name_entry = ttk.Entry(form_grid, textvariable=self.name_var, width=30)
        self.name_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.brand_label = ttk.Label(form_grid, text=self._lang_service.get_text("brand"))
        self.brand_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.brand_var = tk.StringVar()
        self.brand_entry = ttk.Entry(form_grid, textvariable=self.brand_var, width=30)
        self.brand_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.price_label = ttk.Label(form_grid, text=self._lang_service.get_text("price"))
        self.price_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.price_var = tk.DoubleVar()
        self.price_spinbox = ttk.Spinbox(form_grid, from_=0, to=10000,
                                         textvariable=self.price_var,
                                         increment=0.01, width=10)
        self.price_spinbox.grid(row=row, column=1, sticky=tk.W, pady=5, padx=5)
        row += 1

        self.desc_label = ttk.Label(form_grid, text=self._lang_service.get_text("description"))
        self.desc_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.description_text = tk.Text(form_grid, width=30, height=5)
        self.description_text.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.volume_label = ttk.Label(form_grid, text=self._lang_service.get_text("volume"))
        self.volume_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.volume_var = tk.IntVar()
        self.volume_spinbox = ttk.Spinbox(form_grid, from_=0, to=1000,
                                          textvariable=self.volume_var, width=10)
        self.volume_spinbox.grid(row=row, column=1, sticky=tk.W, pady=5, padx=5)
        row += 1

        self.conc_label = ttk.Label(form_grid, text=self._lang_service.get_text("concentration"))
        self.conc_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.concentration_var = tk.StringVar()
        self.concentration_combo = ttk.Combobox(form_grid, textvariable=self.concentration_var,
                                                state="readonly", width=20)

        self.concentration_combo.grid(row=row, column=1, sticky=tk.W, pady=5, padx=5)
        row += 1

        self.gender_label = ttk.Label(form_grid, text=self._lang_service.get_text("gender"))
        self.gender_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.gender_var = tk.StringVar()
        self.gender_combo = ttk.Combobox(form_grid, textvariable=self.gender_var,
                                         state="readonly", width=20)

        self.gender_combo.grid(row=row, column=1, sticky=tk.W, pady=5, padx=5)
        row += 1

        self.image_label = ttk.Label(form_grid, text=self._lang_service.get_text("image"))
        self.image_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        image_frame = ttk.Frame(form_grid)
        image_frame.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)

        self.image_var = tk.StringVar()
        self.image_entry = ttk.Entry(image_frame, textvariable=self.image_var, width=20)
        self.image_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)

        self.browse_button = ttk.Button(image_frame, text=self._lang_service.get_text("browse"))
        self.browse_button.pack(side=tk.RIGHT, padx=5)
        row += 1

        self.preview_label = ttk.Label(form_grid, text=self._lang_service.get_text("preview"))
        self.preview_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.image_preview_frame = ttk.Frame(form_grid, width=200, height=200,
                                             relief=tk.SUNKEN, borderwidth=1)
        self.image_preview_frame.grid(row=row, column=1, sticky=tk.W, pady=5, padx=5)
        self.image_preview_frame.pack_propagate(False)

        self.image_preview = ttk.Label(self.image_preview_frame)
        self.image_preview.pack(fill=tk.BOTH, expand=True)
        row += 1

        self.perfumeries_label = ttk.Label(form_grid, text=self._lang_service.get_text("available_at"))
        self.perfumeries_label.grid(row=row, column=0, sticky=tk.W, pady=5)

        perfumeries_frame = ttk.Frame(form_grid)
        perfumeries_frame.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)

        columns = ('id', 'name', 'city', 'quantity')
        self.perfumeries_table = ttk.Treeview(perfumeries_frame, columns=columns, show='headings', height=5)
        self.perfumeries_table.heading('id', text='ID')
        self.perfumeries_table.heading('name', text=self._lang_service.get_text("name").replace(":", ""))
        self.perfumeries_table.heading('city', text=self._lang_service.get_text("city").replace(":", ""))
        self.perfumeries_table.heading('quantity',
                                       text=self._lang_service.get_text("quantity_availability").replace(":", ""))

        self.perfumeries_table.column('id', width=40, stretch=False)
        self.perfumeries_table.column('name', width=150, stretch=True)
        self.perfumeries_table.column('city', width=100, stretch=True)
        self.perfumeries_table.column('quantity', width=120, stretch=False)

        perfumeries_scrollbar = ttk.Scrollbar(perfumeries_frame, orient="vertical",
                                              command=self.perfumeries_table.yview)
        self.perfumeries_table.configure(yscrollcommand=perfumeries_scrollbar.set)

        self.perfumeries_table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        perfumeries_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        row += 1

        button_frame = ttk.Frame(form_grid)
        button_frame.grid(row=row, column=0, columnspan=2, pady=10)

        self.add_button = ttk.Button(button_frame, text=self._lang_service.get_text("add"))
        self.add_button.pack(side=tk.LEFT, padx=5)

        self.update_button = ttk.Button(button_frame, text=self._lang_service.get_text("update"))
        self.update_button.pack(side=tk.LEFT, padx=5)

        self.delete_button = ttk.Button(button_frame, text=self._lang_service.get_text("delete"))
        self.delete_button.pack(side=tk.LEFT, padx=5)

        self.clear_button = ttk.Button(button_frame, text=self._lang_service.get_text("clear"))
        self.clear_button.pack(side=tk.LEFT, padx=5)

        paned.add(form_outer_frame, weight=4)

        cards_frame = ttk.Frame(paned, padding=10)

        filter_frame = ttk.Frame(cards_frame)
        filter_frame.pack(fill=tk.X, pady=(0, 10))

        search_frame = ttk.Frame(filter_frame)
        search_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        self.search_label = ttk.Label(search_frame, text=self._lang_service.get_text("search"))
        self.search_label.pack(side=tk.LEFT)
        self.search_var = tk.StringVar()
        self.search_entry = ttk.Entry(search_frame, textvariable=self.search_var, width=30)
        self.search_entry.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)

        self.search_button = ttk.Button(search_frame, text=self._lang_service.get_text("search"))
        self.search_button.pack(side=tk.RIGHT)

        brand_frame = ttk.Frame(filter_frame)
        brand_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        self.filter_label = ttk.Label(brand_frame, text=self._lang_service.get_text("filter_brand"))
        self.filter_label.pack(side=tk.LEFT)
        self.filter_brand_var = tk.StringVar()
        self.filter_brand_combo = ttk.Combobox(brand_frame, textvariable=self.filter_brand_var,
                                               width=30, state="readonly")
        self.filter_brand_combo.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)

        sort_frame = ttk.Frame(filter_frame)
        sort_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        self.sort_label = ttk.Label(sort_frame, text=self._lang_service.get_text("sort_by"))
        self.sort_label.pack(side=tk.LEFT)
        self.sort_var = tk.StringVar(value="Name")
        self.sort_combo = ttk.Combobox(sort_frame, textvariable=self.sort_var,
                                       values=["Name", "Brand", "Price"],
                                       state="readonly", width=15)
        self.sort_combo.pack(side=tk.LEFT, padx=5)

        self.sort_desc_var = tk.BooleanVar(value=False)
        self.sort_desc_check = ttk.Checkbutton(sort_frame, text=self._lang_service.get_text("descending"),
                                               variable=self.sort_desc_var)
        self.sort_desc_check.pack(side=tk.LEFT, padx=5)

        self.sort_button = ttk.Button(sort_frame, text=self._lang_service.get_text("sort"))
        self.sort_button.pack(side=tk.LEFT, padx=5)

        self.canvas = tk.Canvas(cards_frame, borderwidth=0, highlightthickness=0)
        scrollbar = ttk.Scrollbar(cards_frame, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=scrollbar.set)

        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.cards_container = ttk.Frame(self.canvas)
        self.canvas_window = self.canvas.create_window((0, 0), window=self.cards_container, anchor="nw")

        paned.add(cards_frame, weight=6)

        paned.sashpos(0, 400)
