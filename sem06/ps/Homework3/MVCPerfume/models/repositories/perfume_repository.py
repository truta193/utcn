from sqlalchemy.orm import Session
from sqlalchemy import asc, desc
from typing import List, Optional
from models.db_models import Perfume


class PerfumeRepository:
    def __init__(self, db: Session):
        self.db = db

    def create(self, name: str, brand: str, price: float, description: str = None,
               volume_ml: int = None, concentration: str = None, gender: str = None,
               image_path: str = None) -> Perfume:
        db_perfume = Perfume(
            name=name,
            brand=brand,
            price=price,
            description=description,
            volume_ml=volume_ml,
            concentration=concentration,
            gender=gender,
            image_path=image_path
        )
        self.db.add(db_perfume)
        self.db.commit()
        self.db.refresh(db_perfume)
        return db_perfume

    def get_by_id(self, perfume_id: int) -> Optional[Perfume]:
        return self.db.query(Perfume).filter(Perfume.id == perfume_id).first()

    def get_all(self, skip: int = 0, limit: int = 100, sort_by: str = "name", sort_desc: bool = False) -> List[Perfume]:
        query = self.db.query(Perfume)

        if sort_by == "name":
            query = query.order_by(desc(Perfume.name) if sort_desc else asc(Perfume.name))
        elif sort_by == "brand":
            query = query.order_by(desc(Perfume.brand) if sort_desc else asc(Perfume.brand))
        elif sort_by == "price":
            query = query.order_by(desc(Perfume.price) if sort_desc else asc(Perfume.price))

        return query.offset(skip).limit(limit).all()

    def filter_by_brand(self, brand: str, skip: int = 0, limit: int = 100) -> List[Perfume]:
        return (self.db.query(Perfume)
                .filter(Perfume.brand.ilike(f"%{brand}%"))
                .offset(skip).limit(limit).all())

    def search_by_name(self, name: str, skip: int = 0, limit: int = 100) -> List[Perfume]:
        return (self.db.query(Perfume)
                .filter(Perfume.name.ilike(f"%{name}%"))
                .offset(skip).limit(limit).all())

    def update(self, perfume_id: int, **kwargs) -> Optional[Perfume]:
        db_perfume = self.get_by_id(perfume_id)
        if db_perfume:
            for key, value in kwargs.items():
                if hasattr(db_perfume, key):
                    setattr(db_perfume, key, value)
            self.db.commit()
            self.db.refresh(db_perfume)
        return db_perfume

    def delete(self, perfume_id: int) -> bool:
        db_perfume = self.get_by_id(perfume_id)
        if db_perfume:
            self.db.delete(db_perfume)
            self.db.commit()
            return True
        return False
