import os
from dotenv import load_dotenv

load_dotenv()

SQLALCHEMY_DATABASE_URL = os.getenv("SQLALCHEMY_DATABASE_URL", "sqlite:///./perfume_app.db")

APP_NAME = os.getenv("APP_NAME", "Perfume App")
DEBUG_MODE = os.getenv("DEBUG_MODE", True)

IMAGE_STORAGE_PATH = os.getenv("IMAGE_STORAGE_PATH", "./static/images/perfumes")
EXPORT_STORAGE_PATH = os.getenv("EXPORT_STORAGE_PATH", "./exports")

API_PREFIX = os.getenv("API_PREFIX", "/api")
