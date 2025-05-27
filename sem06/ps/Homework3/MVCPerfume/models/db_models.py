from sqlalchemy import Column, Integer, String, Float, Text, ForeignKey, Boolean
from sqlalchemy.orm import relationship

from database import Base


class Perfume(Base):
    __tablename__ = "perfumes"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String(100), nullable=False, index=True)
    brand = Column(String(100), nullable=False, index=True)
    description = Column(Text)
    price = Column(Float, nullable=False)
    volume_ml = Column(Integer)
    concentration = Column(String(50))
    gender = Column(String(20))
    image_path = Column(String(255))

    inventories = relationship("Inventory", back_populates="perfume", cascade="all, delete-orphan")

    def __repr__(self):
        return f"<Perfume {self.name} by {self.brand}>"


class Perfumery(Base):
    __tablename__ = "perfumeries"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String(100), nullable=False)
    address = Column(String(255), nullable=False)
    city = Column(String(100), nullable=False)
    phone = Column(String(20))
    email = Column(String(100))
    manager_name = Column(String(100))

    inventories = relationship("Inventory", back_populates="perfumery", cascade="all, delete-orphan")

    def __repr__(self):
        return f"<Perfumery {self.name} ({self.city})>"


class Inventory(Base):
    __tablename__ = "inventories"

    id = Column(Integer, primary_key=True, index=True)
    perfumery_id = Column(Integer, ForeignKey("perfumeries.id"), nullable=False)
    perfume_id = Column(Integer, ForeignKey("perfumes.id"), nullable=False)
    quantity = Column(Integer, default=0)
    is_available = Column(Boolean, default=True)

    perfumery = relationship("Perfumery", back_populates="inventories")
    perfume = relationship("Perfume", back_populates="inventories")

    def __repr__(self):
        return f"<Inventory: {self.perfume.name} at {self.perfumery.name}>"
