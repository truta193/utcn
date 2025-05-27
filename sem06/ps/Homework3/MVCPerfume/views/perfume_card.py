import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import os


class PerfumeCard(ttk.Frame):

    def __init__(self, master, perfume, lang_service=None, **kwargs):

        super().__init__(master, **kwargs)

        self.perfume = perfume
        self.lang_service = lang_service
        self.selected = False
        self.photo = None

        self.configure(relief=tk.RAISED, borderwidth=1, padding=5, width=200, height=250)

        self._create_widgets()

    def _create_widgets(self):

        self.image_frame = ttk.Frame(self, width=180, height=150)
        self.image_frame.pack(fill=tk.X, expand=False, pady=5)
        self.image_frame.pack_propagate(False)

        self.image_label = ttk.Label(self.image_frame)
        self.image_label.pack(fill=tk.BOTH, expand=True)

        if self.perfume.image_path:
            try:
                img_path = os.path.join("images/perfumes", self.perfume.image_path)
                if os.path.exists(img_path):

                    image = Image.open(img_path)
                    image.thumbnail((170, 140), Image.LANCZOS)
                    self.photo = ImageTk.PhotoImage(image)

                    self.image_label.configure(image=self.photo)
                else:
                    self.image_label.configure(text="No Image")
            except Exception as e:
                print(f"Error loading image: {e}")
                self.image_label.configure(text="Error")
        else:
            self.image_label.configure(text="No Image")

        details_frame = ttk.Frame(self)
        details_frame.pack(fill=tk.X, expand=True)

        self.name_label = ttk.Label(details_frame, text=self.perfume.name, font=("", 10, "bold"), wraplength=180)
        self.name_label.pack(fill=tk.X, expand=True)

        self.brand_label = ttk.Label(details_frame, text=self.perfume.brand, font=("", 9), wraplength=180)
        self.brand_label.pack(fill=tk.X, expand=True)

        self.price_label = ttk.Label(details_frame, text=f"${self.perfume.price:.2f}", font=("", 9, "bold"))
        self.price_label.pack(fill=tk.X, expand=True)

        info_parts = []
        if self.perfume.concentration:
            info_parts.append(self.perfume.concentration)
        if self.perfume.volume_ml:
            info_parts.append(f"{self.perfume.volume_ml} ml")
        if self.perfume.gender:
            info_parts.append(self.perfume.gender)

        info_text = " • ".join(info_parts)
        self.info_label = ttk.Label(details_frame, text=info_text, font=("", 8), wraplength=180)
        self.info_label.pack(fill=tk.X, expand=True)
