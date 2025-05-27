import os
import tkinter as tk
from tkinter import ttk, messagebox
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from controllers.inventory_controller import InventoryController
from controllers.perfumery_controller import PerfumeryController
from models.db_models import Base
from controllers.perfume_controller import PerfumeController
from models.viewmodels.observable_inventory_repository import ObservableInventoryRepository
from models.viewmodels.observable_perfume_repository import ObservablePerfumeRepository
from models.viewmodels.observable_perfumery_repository import ObservablePerfumeryRepository
from services.language_service import LanguageService
from views.inventory_view import InventoryView
from views.perfume_view import PerfumeView
from views.perfumery_view import PerfumeryView


class MainApplication(tk.Tk):
    def __init__(self):
        super().__init__()

        self._lang_service = LanguageService()

        self.title(self._lang_service.get_text("title"))
        self.geometry("1200x700")

        self.db = self._setup_database()

        self.perfume_repository = ObservablePerfumeRepository(self.db)

        self.perfumery_repository = ObservablePerfumeryRepository(self.db)
        self.inventory_repository = ObservableInventoryRepository(self.db)

        self._init_ui()

        self._create_controllers()

        self._lang_service.add_listener(self)

        self._setup_directories()

    def _init_ui(self):

        main_frame = ttk.Frame(self, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        lang_frame = ttk.Frame(main_frame)
        lang_frame.pack(fill=tk.X, pady=(0, 10))

        ttk.Label(lang_frame, text=self._lang_service.get_text("language")).pack(side=tk.LEFT)
        self.language_var = tk.StringVar(value=self._lang_service.get_language_names()[0])
        language_combo = ttk.Combobox(lang_frame, textvariable=self.language_var,
                                      values=self._lang_service.get_language_names(),
                                      state="readonly", width=15)
        language_combo.pack(side=tk.LEFT, padx=5)
        language_combo.bind("<<ComboboxSelected>>", self._on_language_changed)

        self.notebook = ttk.Notebook(main_frame)
        self.notebook.pack(fill=tk.BOTH, expand=True)

        self.perfume_view = PerfumeView(self.notebook)
        self.notebook.add(self.perfume_view, text=self._lang_service.get_text("perfumes"))

        self.perfumery_view = PerfumeryView(self.notebook)
        self.notebook.add(self.perfumery_view, text=self._lang_service.get_text("perfumeries"))

        self.inventory_view = InventoryView(self.notebook)
        self.notebook.add(self.inventory_view, text=self._lang_service.get_text("inventory"))

        self.status_var = tk.StringVar(value=self._lang_service.get_text("ready"))
        self.status_bar = ttk.Label(main_frame, textvariable=self.status_var,
                                    relief=tk.SUNKEN, anchor=tk.W)
        self.status_bar.pack(fill=tk.X, side=tk.BOTTOM, pady=(5, 0))

    def _create_controllers(self):

        self.perfume_controller = PerfumeController(
            self.perfume_repository,
            self.perfumery_repository,
            self.inventory_repository,
            self.perfume_view
        )

        self.perfumery_controller = PerfumeryController(
            self.perfumery_repository,
            self.inventory_repository,
            self.perfume_repository,
            self.perfumery_view
        )

        self.inventory_controller = InventoryController(
            self.perfumery_repository,
            self.perfume_repository,
            self.inventory_repository,
            self.inventory_view
        )

    def _setup_database(self):
        os.makedirs("data", exist_ok=True)

        engine = create_engine("sqlite:///data/perfumes.db", connect_args={"check_same_thread": False})

        Base.metadata.create_all(engine)

        SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

        return SessionLocal()

    def _setup_directories(self):
        os.makedirs("images/perfumes", exist_ok=True)
        print(f"Created directory: {os.path.abspath('images/perfumes')}")

    def _on_language_changed(self, event):
        selection = self.language_var.get()
        language_names = self._lang_service.get_language_names()
        language_codes = self._lang_service.get_languages()

        if selection in language_names:
            index = language_names.index(selection)
            if index < len(language_codes):
                self._lang_service.set_language(language_codes[index])

    def on_language_changed(self, language_code):

        self.title(self._lang_service.get_text("title"))

        self.notebook.tab(0, text=self._lang_service.get_text("perfumes"))
        self.notebook.tab(1, text=self._lang_service.get_text("perfumeries"))
        self.notebook.tab(2, text=self._lang_service.get_text("inventory"))

        if self.status_var.get() == "Ready" or self.status_var.get() == "Prêt" or self.status_var.get() == "Listo":
            self.status_var.set(self._lang_service.get_text("ready"))

    def show_message(self, message):
        self.status_var.set(message)
        self.after(3000, lambda: self.status_var.set(self._lang_service.get_text("ready")))

    def show_error(self, message):
        messagebox.showerror(self._lang_service.get_text("error"), message)


def main():
    app = MainApplication()
    app.mainloop()


if __name__ == "__main__":
    main()
