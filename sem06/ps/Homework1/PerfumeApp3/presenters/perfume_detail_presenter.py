import os
from sqlalchemy.orm import Session
from typing import List, Dict, Any, Optional

from models.repository.perfume_repository import PerfumeRepository
from models.repository.inventory_repository import InventoryRepository
from presenters.interfaces import PerfumeDetailViewInterface
from schemas.perfume_schemas import PerfumeCreate, PerfumeUpdate
from config import IMAGE_STORAGE_PATH


class PerfumeDetailPresenter:

    def __init__(self, db: Session, view: PerfumeDetailViewInterface):
        self.db = db
        self.view = view
        self.perfume_repository = PerfumeRepository(db)
        self.inventory_repository = InventoryRepository(db)
        self.image_dir = IMAGE_STORAGE_PATH
        os.makedirs(self.image_dir, exist_ok=True)

    def show_perfume(self, perfume_id: int) -> None:
        try:
            perfume = self.perfume_repository.get_by_id(perfume_id)
            if not perfume:
                self.view.display_error("Perfume not found")
                self.view.redirect_to_list()
                return

            inventories = self.inventory_repository.get_all_by_perfume(perfume_id)

            perfume_data = self._convert_perfume_to_dict(perfume)
            availability_data = []

            for inv in inventories:
                if inv.is_available and inv.quantity > 0:
                    print("inv.perfumery.id", inv.perfumery.id)
                    availability_data.append({
                        'perfumery_id': inv.perfumery.id,
                        'perfumery_name': inv.perfumery.name,
                        'perfumery_city': inv.perfumery.city,
                        'quantity': inv.quantity
                    })

            self.view.display_perfume(perfume_data, availability_data)
            return self.view.display_perfume(perfume_data, availability_data)

        except Exception as e:
            self.view.display_error(str(e))
            self.view.redirect_to_list()
            return self.view.redirect_to_list()

    def show_create_form(self) -> None:
        self.view.show_create_form()
        return self.view.show_create_form()

    def create_perfume(self, form_data: Dict[str, Any], image=None) -> None:
        try:
            perfume_data = PerfumeCreate(
                name=form_data['name'],
                brand=form_data['brand'],
                price=float(form_data['price']),
                description=form_data.get('description'),
                volume_ml=int(form_data['volume_ml']) if form_data.get('volume_ml') else None,
                concentration=form_data.get('concentration'),
                gender=form_data.get('gender')
            )

            image_path = None
            if image and hasattr(image, 'filename') and image.filename:
                file_extension = os.path.splitext(image.filename)[1]
                image_name = f"{perfume_data.brand}_{perfume_data.name}_{perfume_data.volume_ml}ml{file_extension}".lower().replace(
                    " ", "_")
                image_path = os.path.join(self.image_dir, image_name)

                image.save(image_path)

            new_perfume = self.perfume_repository.create(
                name=perfume_data.name,
                brand=perfume_data.brand,
                price=perfume_data.price,
                description=perfume_data.description,
                volume_ml=perfume_data.volume_ml,
                concentration=perfume_data.concentration,
                gender=perfume_data.gender,
                image_path=image_path
            )

            self.view.display_success("Perfume created successfully!")
            self.view.redirect_to_detail(new_perfume.id)
            return self.view.redirect_to_detail(new_perfume.id)

        except Exception as e:
            self.view.display_error(f"Error creating perfume: {str(e)}")
            self.view.show_create_form()
            return self.view.show_create_form()

    def show_edit_form(self, perfume_id: int) -> None:
        try:
            perfume = self.perfume_repository.get_by_id(perfume_id)
            if not perfume:
                self.view.display_error("Perfume not found")
                self.view.redirect_to_list()
                return

            perfume_data = self._convert_perfume_to_dict(perfume)

            self.view.show_edit_form(perfume_data)
            return self.view.show_edit_form(perfume_data)

        except Exception as e:
            self.view.display_error(str(e))
            self.view.redirect_to_list()
            return self.view.redirect_to_list()

    def update_perfume(self, perfume_id: int, form_data: Dict[str, Any], image=None) -> None:
        try:
            db_perfume = self.perfume_repository.get_by_id(perfume_id)
            if not db_perfume:
                self.view.display_error("Perfume not found")
                self.view.redirect_to_list()
                return

            update_data = {}
            if form_data.get('name'):
                update_data['name'] = form_data['name']
            if form_data.get('brand'):
                update_data['brand'] = form_data['brand']
            if form_data.get('price'):
                update_data['price'] = float(form_data['price'])
            if 'description' in form_data:
                update_data['description'] = form_data['description']
            if form_data.get('volume_ml'):
                update_data['volume_ml'] = int(form_data['volume_ml'])
            if form_data.get('concentration'):
                update_data['concentration'] = form_data['concentration']
            if form_data.get('gender'):
                update_data['gender'] = form_data['gender']

            if image and hasattr(image, 'filename') and image.filename:
                # Remove old image if it exists
                if db_perfume.image_path and os.path.exists(db_perfume.image_path):
                    os.remove(db_perfume.image_path)

                file_extension = os.path.splitext(image.filename)[1]
                name = update_data.get('name', db_perfume.name)
                brand = update_data.get('brand', db_perfume.brand)
                volume = update_data.get('volume_ml', db_perfume.volume_ml)

                image_name = f"{brand}_{name}_{volume}ml{file_extension}".lower().replace(" ", "_")
                image_path = os.path.join(self.image_dir, image_name)

                image.save(image_path)
                update_data['image_path'] = image_path

            perfume_update = PerfumeUpdate(**update_data)
            updated_perfume = self.perfume_repository.update(perfume_id, **perfume_update.dict(exclude_unset=True))

            if not updated_perfume:
                self.view.display_error("Failed to update perfume")
                self.view.redirect_to_list()
                return

            self.view.display_success("Perfume updated successfully!")
            self.view.redirect_to_detail(perfume_id)
            return self.view.redirect_to_detail(perfume_id)

        except Exception as e:
            self.view.display_error(f"Error updating perfume: {str(e)}")
            self.view.show_edit_form(self._convert_perfume_to_dict(db_perfume))
            return self.view.show_edit_form(self._convert_perfume_to_dict(db_perfume))

    def delete_perfume(self, perfume_id: int) -> None:
        try:
            db_perfume = self.perfume_repository.get_by_id(perfume_id)
            if not db_perfume:
                self.view.display_error("Perfume not found")
                self.view.redirect_to_list()
                return

            if db_perfume.image_path and os.path.exists(db_perfume.image_path):
                os.remove(db_perfume.image_path)

            success = self.perfume_repository.delete(perfume_id)

            if not success:
                self.view.display_error("Failed to delete perfume")
            else:
                self.view.display_success("Perfume deleted successfully!")

            self.view.redirect_to_list()
            return self.view.redirect_to_list()

        except Exception as e:
            self.view.display_error(f"Error deleting perfume: {str(e)}")
            self.view.redirect_to_list()
            return self.view.redirect_to_list()

    def _convert_perfume_to_dict(self, perfume) -> Dict[str, Any]:
        image_url = None
        if perfume.image_path:
            image_url = f"/static/images/perfumes/{os.path.basename(perfume.image_path)}"

        return {
            'id': perfume.id,
            'name': perfume.name,
            'brand': perfume.brand,
            'price': perfume.price,
            'description': perfume.description,
            'volume_ml': perfume.volume_ml,
            'concentration': perfume.concentration,
            'gender': perfume.gender,
            'image_path': image_url
        }