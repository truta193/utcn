from sqlalchemy.orm import Session
from typing import List, Optional

from models.db_models import Inventory


class InventoryRepository:
    def __init__(self, db: Session):
        self.db = db

    def create(self, perfumery_id: int, perfume_id: int, quantity: int = 0,
               is_available: bool = True) -> Inventory:
        db_inventory = Inventory(
            perfumery_id=perfumery_id,
            perfume_id=perfume_id,
            quantity=quantity,
            is_available=is_available,
        )

        self.db.add(db_inventory)
        self.db.commit()
        self.db.refresh(db_inventory)
        return db_inventory

    def get_by_id(self, inventory_id: int) -> Optional[Inventory]:
        return self.db.query(Inventory).filter(Inventory.id == inventory_id).first()

    def get_by_perfumery_and_perfume(self, perfumery_id: int, perfume_id: int) -> Optional[Inventory]:
        return self.db.query(Inventory).filter(
            Inventory.perfumery_id == perfumery_id,
            Inventory.perfume_id == perfume_id
        ).first()

    def get_all_by_perfumery(self, perfumery_id: int, skip: int = 0, limit: int = 100) -> List[Inventory]:
        return self.db.query(Inventory).filter(
            Inventory.perfumery_id == perfumery_id
        ).offset(skip).limit(limit).all()

    def get_all_by_perfume(self, perfume_id: int, skip: int = 0, limit: int = 100) -> List[Inventory]:
        return self.db.query(Inventory).filter(
            Inventory.perfume_id == perfume_id
        ).offset(skip).limit(limit).all()

    def get_out_of_stock_by_perfumery(self, perfumery_id: int) -> List[Inventory]:
        return self.db.query(Inventory).filter(
            Inventory.perfumery_id == perfumery_id,
            Inventory.quantity == 0
        ).all()

    def get_by_availability(self, perfumery_id: int, is_available: bool) -> List[Inventory]:
        return self.db.query(Inventory).filter(
            Inventory.perfumery_id == perfumery_id,
            Inventory.is_available == is_available
        ).all()

    def update(self, inventory_id: int, **kwargs) -> Optional[Inventory]:
        db_inventory = self.get_by_id(inventory_id)
        if db_inventory:
            for key, value in kwargs.items():
                if hasattr(db_inventory, key):
                    setattr(db_inventory, key, value)

            # If updating quantity to > 0, ensure is_available is True
            if 'quantity' in kwargs and kwargs['quantity'] > 0:
                db_inventory.is_available = True

            # If updating quantity to 0, ensure is_available is False
            elif 'quantity' in kwargs and kwargs['quantity'] == 0:
                db_inventory.is_available = False
            self.db.commit()
            self.db.refresh(db_inventory)
        return db_inventory

    def delete(self, inventory_id: int) -> bool:
        db_inventory = self.get_by_id(inventory_id)
        if db_inventory:
            self.db.delete(db_inventory)
            self.db.commit()
            return True
        return False

    def get_all(self, skip: int = 0, limit: int = 100) -> List[Inventory]:

        return self.db.query(Inventory).offset(skip).limit(limit).all()
