import tkinter as tk
from tkinter import ttk
from views.base_view import BaseView


class PerfumeryView(BaseView):

    def __init__(self, parent):
        super().__init__(parent)

        self._current_perfumery_id = None
        self._perfumeries = []

        self._init_ui()

    def _init_ui(self):
        main_frame = ttk.Frame(self, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        paned = ttk.PanedWindow(main_frame, orient=tk.HORIZONTAL)
        paned.pack(fill=tk.BOTH, expand=True)

        form_outer_frame = ttk.Frame(paned)

        self.perfumery_form_canvas = tk.Canvas(form_outer_frame, borderwidth=0, highlightthickness=0)
        form_scrollbar = ttk.Scrollbar(form_outer_frame, orient="vertical", command=self.perfumery_form_canvas.yview)
        self.perfumery_form_canvas.configure(yscrollcommand=form_scrollbar.set)

        form_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.perfumery_form_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        form_frame = ttk.LabelFrame(self.perfumery_form_canvas, text="Perfumery Details", padding=10)
        self.perfumery_form_window = self.perfumery_form_canvas.create_window((0, 0), window=form_frame, anchor="nw")

        self.perfumery_form_canvas.bind("<Configure>", lambda e: self._on_perfumery_canvas_configure(e))
        form_frame.bind("<Configure>", lambda e: self.perfumery_form_canvas.configure(
            scrollregion=self.perfumery_form_canvas.bbox("all")))

        form_grid = ttk.Frame(form_frame)
        form_grid.pack(fill=tk.BOTH, expand=True)

        row = 0

        self.perfumery_name_label = ttk.Label(form_grid, text="Name:")
        self.perfumery_name_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.perfumery_name_var = tk.StringVar()
        self.perfumery_name_entry = ttk.Entry(form_grid, textvariable=self.perfumery_name_var, width=30)
        self.perfumery_name_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.address_label = ttk.Label(form_grid, text="Address:")
        self.address_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.address_var = tk.StringVar()
        self.address_entry = ttk.Entry(form_grid, textvariable=self.address_var, width=30)
        self.address_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.city_label = ttk.Label(form_grid, text="City:")
        self.city_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.city_var = tk.StringVar()
        self.city_entry = ttk.Entry(form_grid, textvariable=self.city_var, width=30)
        self.city_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.phone_label = ttk.Label(form_grid, text="Phone:")
        self.phone_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.phone_var = tk.StringVar()
        self.phone_entry = ttk.Entry(form_grid, textvariable=self.phone_var, width=30)
        self.phone_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.email_label = ttk.Label(form_grid, text="Email:")
        self.email_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.email_var = tk.StringVar()
        self.email_entry = ttk.Entry(form_grid, textvariable=self.email_var, width=30)
        self.email_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.manager_label = ttk.Label(form_grid, text="Manager:")
        self.manager_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.manager_var = tk.StringVar()
        self.manager_entry = ttk.Entry(form_grid, textvariable=self.manager_var, width=30)
        self.manager_entry.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.inventory_summary_label = ttk.Label(form_grid, text="Inventory Summary:")
        self.inventory_summary_label.grid(row=row, column=0, sticky=tk.W, pady=5)

        inventory_frame = ttk.Frame(form_grid)
        inventory_frame.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)

        columns = ('id', 'name', 'brand', 'quantity', 'available')
        self.inventory_summary_table = ttk.Treeview(inventory_frame, columns=columns, show='headings', height=5)
        self.inventory_summary_table.heading('id', text='ID')
        self.inventory_summary_table.heading('name', text='Name')
        self.inventory_summary_table.heading('brand', text='Brand')
        self.inventory_summary_table.heading('quantity', text='Quantity')
        self.inventory_summary_table.heading('available', text='Available')

        self.inventory_summary_table.column('id', width=40, stretch=False)
        self.inventory_summary_table.column('name', width=150, stretch=True)
        self.inventory_summary_table.column('brand', width=100, stretch=True)
        self.inventory_summary_table.column('quantity', width=70, stretch=False)
        self.inventory_summary_table.column('available', width=70, stretch=False)

        inventory_scrollbar = ttk.Scrollbar(inventory_frame, orient="vertical",
                                            command=self.inventory_summary_table.yview)
        self.inventory_summary_table.configure(yscrollcommand=inventory_scrollbar.set)

        self.inventory_summary_table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        inventory_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        row += 1

        self.stats_label = ttk.Label(form_grid, text="Statistics:")
        self.stats_label.grid(row=row, column=0, sticky=tk.W, pady=5)

        stats_container = ttk.Frame(form_grid)
        stats_container.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)

        self.gender_chart_frame = ttk.LabelFrame(stats_container, text="Gender Distribution")
        self.gender_chart_frame.pack(fill=tk.BOTH, expand=True, pady=5, ipady=100)

        self.brand_chart_frame = ttk.LabelFrame(stats_container, text="Brand Distribution")
        self.brand_chart_frame.pack(fill=tk.BOTH, expand=True, pady=5, ipady=100)

        row += 1

        button_frame = ttk.Frame(form_grid)
        button_frame.grid(row=row, column=0, columnspan=2, pady=10)

        self.add_perfumery_button = ttk.Button(button_frame, text="Add")
        self.add_perfumery_button.pack(side=tk.LEFT, padx=5)

        self.update_perfumery_button = ttk.Button(button_frame, text="Update")
        self.update_perfumery_button.pack(side=tk.LEFT, padx=5)

        self.delete_perfumery_button = ttk.Button(button_frame, text="Delete")
        self.delete_perfumery_button.pack(side=tk.LEFT, padx=5)

        self.clear_perfumery_button = ttk.Button(button_frame, text="Clear")
        self.clear_perfumery_button.pack(side=tk.LEFT, padx=5)

        self.export_csv_button = ttk.Button(button_frame, text="Export CSV")
        self.export_csv_button.pack(side=tk.BOTTOM, padx=5)

        self.export_doc_button = ttk.Button(button_frame, text="Export DOC")
        self.export_doc_button.pack(side=tk.LEFT, padx=5)

        paned.add(form_outer_frame, weight=7)

        list_frame = ttk.Frame(paned, padding=10)

        filter_frame = ttk.Frame(list_frame)
        filter_frame.pack(fill=tk.X, pady=(0, 10))

        city_frame = ttk.Frame(filter_frame)
        city_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        list_container = ttk.Frame(list_frame)
        list_container.pack(fill=tk.BOTH, expand=True)

        columns = ('id', 'name', 'city', 'phone')
        self.perfumeries_table = ttk.Treeview(list_container, columns=columns, show='headings')
        self.perfumeries_table.heading('id', text='ID')
        self.perfumeries_table.heading('name', text='Name')
        self.perfumeries_table.heading('city', text='City')
        self.perfumeries_table.heading('phone', text='Phone')

        self.perfumeries_table.column('id', width=40, stretch=False)
        self.perfumeries_table.column('name', width=200, stretch=True)
        self.perfumeries_table.column('city', width=100, stretch=True)
        self.perfumeries_table.column('phone', width=120, stretch=False)

        perfumeries_scrollbar = ttk.Scrollbar(list_container, orient="vertical", command=self.perfumeries_table.yview)
        self.perfumeries_table.configure(yscrollcommand=perfumeries_scrollbar.set)

        self.perfumeries_table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        perfumeries_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        paned.add(list_frame, weight=3)

        paned.sashpos(0, 650)

    def _on_perfumery_canvas_configure(self, event):
        self.perfumery_form_canvas.configure(scrollregion=self.perfumery_form_canvas.bbox("all"))

        self.perfumery_form_canvas.itemconfig(self.perfumery_form_window, width=event.width)
