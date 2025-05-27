from flask import render_template, redirect, url_for, send_from_directory
import os

from config import IMAGE_STORAGE_PATH

def home():
    return render_template('home.html')

def serve_image(filename):
    return send_from_directory(IMAGE_STORAGE_PATH, filename)

def not_found_error(error):
    return render_template('errors/404.html'), 404

def internal_error(error):
    return render_template('errors/500.html'), 500