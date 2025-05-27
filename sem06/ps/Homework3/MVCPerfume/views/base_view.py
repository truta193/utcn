import tkinter as tk
from tkinter import ttk
from models.observer import Observer
from services.language_service import LanguageService


class BaseView(ttk.Frame, Observer):

    def __init__(self, parent):
        super().__init__(parent)

        self._lang_service = LanguageService()
        self._lang_service.add_listener(self)

        self.pack(fill=tk.BOTH, expand=True)

    def show_message(self, message):
        if hasattr(self.winfo_toplevel(), 'show_message'):
            self.winfo_toplevel().show_message(message)
