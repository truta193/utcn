from pydantic import BaseModel, Field
from typing import Optional


class InventoryBase(BaseModel):
    perfumery_id: int
    perfume_id: int
    quantity: int = Field(0, ge=0)
    is_available: Optional[bool] = Field(True)


class InventoryCreate(InventoryBase):
    pass


class InventoryUpdate(BaseModel):
    quantity: Optional[int] = Field(None, ge=0)
    is_available: Optional[bool] = None


class InventoryInDB(InventoryBase):
    id: int

    class Config:
        orm_mode = True


class Inventory(InventoryInDB):
    pass
