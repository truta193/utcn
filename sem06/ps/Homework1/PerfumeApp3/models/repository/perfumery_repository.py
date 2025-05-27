from sqlalchemy.orm import Session
from typing import List, Optional

from models.db_models import Perfumery


class PerfumeryRepository:
    def __init__(self, db: Session):
        self.db = db

    def create(self, name: str, address: str, city: str, phone: str = None,
               email: str = None, manager_name: str = None) -> Perfumery:
        db_perfumery = Perfumery(
            name=name,
            address=address,
            city=city,
            phone=phone,
            email=email,
            manager_name=manager_name
        )
        self.db.add(db_perfumery)
        self.db.commit()
        self.db.refresh(db_perfumery)
        return db_perfumery

    def get_by_id(self, perfumery_id: int) -> Optional[Perfumery]:
        return self.db.query(Perfumery).filter(Perfumery.id == perfumery_id).first()

    def get_all(self, skip: int = 0, limit: int = 100) -> List[Perfumery]:
        return self.db.query(Perfumery).offset(skip).limit(limit).all()

    def update(self, perfumery_id: int, **kwargs) -> Optional[Perfumery]:
        db_perfumery = self.get_by_id(perfumery_id)
        if db_perfumery:
            for key, value in kwargs.items():
                if hasattr(db_perfumery, key):
                    setattr(db_perfumery, key, value)
            self.db.commit()
            self.db.refresh(db_perfumery)
        return db_perfumery

    def delete(self, perfumery_id: int) -> bool:
        db_perfumery = self.get_by_id(perfumery_id)
        if db_perfumery:
            self.db.delete(db_perfumery)
            self.db.commit()
            return True
        return False
