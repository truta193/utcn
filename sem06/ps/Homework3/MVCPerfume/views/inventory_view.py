import tkinter as tk
from tkinter import ttk
from views.base_view import BaseView


class InventoryView(BaseView):

    def __init__(self, parent):
        super().__init__(parent)

        self._current_inventory_id = None

        self._init_ui()

    def _init_ui(self):
        main_frame = ttk.Frame(self, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        paned = ttk.PanedWindow(main_frame, orient=tk.HORIZONTAL)
        paned.pack(fill=tk.BOTH, expand=True)

        form_frame = ttk.LabelFrame(paned, text="Inventory Details", padding=10)

        form_grid = ttk.Frame(form_frame)
        form_grid.pack(fill=tk.BOTH, expand=True)

        row = 0

        self.inv_perfumery_label = ttk.Label(form_grid, text="Perfumery:")
        self.inv_perfumery_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.inv_perfumery_var = tk.StringVar()
        self.inv_perfumery_combo = ttk.Combobox(form_grid, textvariable=self.inv_perfumery_var,
                                                state="readonly", width=30)
        self.inv_perfumery_combo.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.inv_perfume_label = ttk.Label(form_grid, text="Perfume:")
        self.inv_perfume_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.inv_perfume_var = tk.StringVar()
        self.inv_perfume_combo = ttk.Combobox(form_grid, textvariable=self.inv_perfume_var,
                                              state="readonly", width=30)
        self.inv_perfume_combo.grid(row=row, column=1, sticky=tk.W + tk.E, pady=5, padx=5)
        row += 1

        self.inv_quantity_label = ttk.Label(form_grid, text="Quantity:")
        self.inv_quantity_label.grid(row=row, column=0, sticky=tk.W, pady=5)
        self.inv_quantity_var = tk.IntVar(value=0)
        self.inv_quantity_spinbox = ttk.Spinbox(form_grid, from_=0, to=1000,
                                                textvariable=self.inv_quantity_var, width=10)
        self.inv_quantity_spinbox.grid(row=row, column=1, sticky=tk.W, pady=5, padx=5)
        row += 1

        button_frame = ttk.Frame(form_grid)
        button_frame.grid(row=row, column=0, columnspan=2, pady=10)

        self.add_inventory_button = ttk.Button(button_frame, text="Add")
        self.add_inventory_button.pack(side=tk.LEFT, padx=5)

        self.update_inventory_button = ttk.Button(button_frame, text="Update")
        self.update_inventory_button.pack(side=tk.LEFT, padx=5)

        self.delete_inventory_button = ttk.Button(button_frame, text="Delete")
        self.delete_inventory_button.pack(side=tk.LEFT, padx=5)

        self.clear_inventory_button = ttk.Button(button_frame, text="Clear")
        self.clear_inventory_button.pack(side=tk.LEFT, padx=5)

        paned.add(form_frame, weight=4)

        list_frame = ttk.Frame(paned, padding=10)

        filter_frame = ttk.Frame(list_frame)
        filter_frame.pack(fill=tk.X, pady=(0, 10))

        perfumery_frame = ttk.Frame(filter_frame)
        perfumery_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        self.filter_inv_perfumery_label = ttk.Label(perfumery_frame, text="Perfumery:")
        self.filter_inv_perfumery_label.pack(side=tk.LEFT)
        self.filter_inv_perfumery_var = tk.StringVar()
        self.filter_inv_perfumery_combo = ttk.Combobox(perfumery_frame, textvariable=self.filter_inv_perfumery_var,
                                                       width=30, state="readonly")
        self.filter_inv_perfumery_combo.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)

        availability_frame = ttk.Frame(filter_frame)
        availability_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        self.filter_availability_label = ttk.Label(availability_frame, text="Show:")
        self.filter_availability_label.pack(side=tk.LEFT)
        self.filter_availability_var = tk.StringVar(value="All Items")
        self.filter_availability_combo = ttk.Combobox(availability_frame, textvariable=self.filter_availability_var,
                                                      values=["All Items", "Available Only", "Out of Stock Only"],
                                                      state="readonly", width=20)
        self.filter_availability_combo.pack(side=tk.LEFT, padx=5)

        self.apply_filter_button = ttk.Button(availability_frame, text="Apply Filter")
        self.apply_filter_button.pack(side=tk.LEFT, padx=5)

        list_container = ttk.Frame(list_frame)
        list_container.pack(fill=tk.BOTH, expand=True)

        columns = ('id', 'perfumery', 'perfume', 'brand', 'quantity', 'available')
        self.inventory_table = ttk.Treeview(list_container, columns=columns, show='headings')
        self.inventory_table.heading('id', text='ID')
        self.inventory_table.heading('perfumery', text='Perfumery')
        self.inventory_table.heading('perfume', text='Perfume')
        self.inventory_table.heading('brand', text='Brand')
        self.inventory_table.heading('quantity', text='Quantity')
        self.inventory_table.heading('available', text='Available')

        self.inventory_table.column('id', width=40, stretch=False)
        self.inventory_table.column('perfumery', width=150, stretch=True)
        self.inventory_table.column('perfume', width=150, stretch=True)
        self.inventory_table.column('brand', width=100, stretch=True)
        self.inventory_table.column('quantity', width=70, stretch=False)
        self.inventory_table.column('available', width=70, stretch=False)

        inventory_scrollbar = ttk.Scrollbar(list_container, orient="vertical", command=self.inventory_table.yview)
        self.inventory_table.configure(yscrollcommand=inventory_scrollbar.set)

        self.inventory_table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        inventory_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        paned.add(list_frame, weight=6)

        paned.sashpos(0, 350)
