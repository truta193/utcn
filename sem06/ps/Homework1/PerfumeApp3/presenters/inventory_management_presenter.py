import os
from sqlalchemy.orm import Session
from typing import List, Dict, Any, Optional
from datetime import datetime

from models.repository.inventory_repository import InventoryRepository
from models.repository.perfume_repository import PerfumeRepository
from models.repository.perfumery_repository import PerfumeryRepository
from presenters.interfaces import InventoryManagementViewInterface
from schemas.inventory_schemas import InventoryCreate, InventoryUpdate


class InventoryManagementPresenter:

    def __init__(self, db: Session, view: InventoryManagementViewInterface):
        self.db = db
        self.view = view
        self.inventory_repository = InventoryRepository(db)
        self.perfume_repository = PerfumeRepository(db)
        self.perfumery_repository = PerfumeryRepository(db)

    def show_create_form(self):
        try:
            perfumes = self.perfume_repository.get_all()
            perfumeries = self.perfumery_repository.get_all()

            perfume_dicts = []
            for p in perfumes:
                perfume_dicts.append({
                    'id': p.id,
                    'name': p.name,
                    'brand': p.brand,
                    'price': p.price
                })

            perfumery_dicts = []
            for p in perfumeries:
                perfumery_dicts.append({
                    'id': p.id,
                    'name': p.name,
                    'city': p.city
                })

            return self.view.show_create_form(perfume_dicts, perfumery_dicts)

        except Exception as e:
            return self.view.display_error(str(e))

    def create_inventory(self, form_data: Dict[str, Any]):
        try:
            inventory_data = InventoryCreate(
                perfumery_id=int(form_data['perfumery_id']),
                perfume_id=int(form_data['perfume_id']),
                quantity=int(form_data['quantity']),
                is_available=int(form_data['quantity']) > 0
            )

            existing = self.inventory_repository.get_by_perfumery_and_perfume(
                inventory_data.perfumery_id, inventory_data.perfume_id
            )

            if existing:
                self.view.display_error("This perfume is already in the inventory for this perfumery")
                return self.view.redirect_to_perfumery(inventory_data.perfumery_id)

            new_inventory = self.inventory_repository.create(
                perfumery_id=inventory_data.perfumery_id,
                perfume_id=inventory_data.perfume_id,
                quantity=inventory_data.quantity,
                is_available=inventory_data.is_available
            )

            self.view.display_success("Inventory item added successfully!")
            return self.view.redirect_to_perfumery(new_inventory.perfumery_id)

        except Exception as e:
            self.view.display_error(f"Error adding inventory: {str(e)}")
            return self.show_create_form()

    def show_edit_form(self, inventory_id: int):
        try:
            inventory = self.inventory_repository.get_by_id(inventory_id)
            if not inventory:
                self.view.display_error("Inventory item not found")
                return self.view.redirect_to_perfumery(1)

            inventory_data = {
                'id': inventory.id,
                'perfume_id': inventory.perfume.id,
                'perfume_name': inventory.perfume.name,
                'perfume_brand': inventory.perfume.brand,
                'perfume_price': inventory.perfume.price,
                'perfumery_id': inventory.perfumery.id,
                'perfumery_name': inventory.perfumery.name,
                'perfumery_city': inventory.perfumery.city,
                'quantity': inventory.quantity,
                'is_available': inventory.is_available
            }

            if inventory.perfume.image_path:
                inventory_data[
                    'image_url'] = f"/static/images/perfumes/{os.path.basename(inventory.perfume.image_path)}"

            return self.view.show_edit_form(inventory_data)

        except Exception as e:
            self.view.display_error(str(e))
            return self.view.redirect_to_perfumery(1)

    def update_inventory(self, inventory_id: int, form_data: Dict[str, Any]):
        try:
            inventory = self.inventory_repository.get_by_id(inventory_id)
            if not inventory:
                self.view.display_error("Inventory item not found")
                return self.view.redirect_to_perfumery(1)

            perfumery_id = inventory.perfumery_id

            quantity = int(form_data['quantity'])
            inventory_data = InventoryUpdate(
                quantity=quantity,
                is_available=quantity > 0
            )

            updated_inventory = self.inventory_repository.update(
                inventory_id,
                **inventory_data.dict(exclude_unset=True)
            )

            if not updated_inventory:
                self.view.display_error("Failed to update inventory")
                return self.view.redirect_to_perfumery(perfumery_id)

            self.view.display_success("Inventory updated successfully!")
            return self.view.redirect_to_perfumery(perfumery_id)

        except Exception as e:
            self.view.display_error(f"Error updating inventory: {str(e)}")
            return self.show_edit_form(inventory_id)

    def delete_inventory(self, inventory_id: int):
        try:
            inventory = self.inventory_repository.get_by_id(inventory_id)
            if not inventory:
                self.view.display_error("Inventory item not found")
                return self.view.redirect_to_perfumery(1)

            perfumery_id = inventory.perfumery_id

            success = self.inventory_repository.delete(inventory_id)

            if not success:
                self.view.display_error("Failed to delete inventory item")
            else:
                self.view.display_success("Inventory item removed successfully!")

            return self.view.redirect_to_perfumery(perfumery_id)

        except Exception as e:
            self.view.display_error(f"Error deleting inventory: {str(e)}")
            return self.view.redirect_to_perfumery(1)