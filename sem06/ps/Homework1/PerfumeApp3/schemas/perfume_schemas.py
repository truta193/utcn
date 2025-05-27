from pydantic import BaseModel, Field
from typing import Optional


class PerfumeBase(BaseModel):
    name: str = Field(..., min_length=1, max_length=100)
    brand: str = Field(..., min_length=1, max_length=100)
    description: Optional[str] = None
    price: float = Field(..., ge=0)
    volume_ml: Optional[int] = Field(None, ge=0)
    concentration: Optional[str] = Field(None, max_length=50)
    gender: Optional[str] = Field(None, max_length=20)
    image_path: Optional[str] = Field(None, max_length=255)


class PerfumeCreate(PerfumeBase):
    pass


class PerfumeUpdate(BaseModel):
    name: Optional[str] = Field(None, min_length=1, max_length=100)
    brand: Optional[str] = Field(None, min_length=1, max_length=100)
    description: Optional[str] = None
    price: Optional[float] = Field(None, ge=0)
    volume_ml: Optional[int] = Field(None, ge=0)
    concentration: Optional[str] = Field(None, max_length=50)
    gender: Optional[str] = Field(None, max_length=20)
    image_path: Optional[str] = Field(None, max_length=255)


class PerfumeInDB(PerfumeBase):
    id: int

    class Config:
        orm_mode = True


class Perfume(PerfumeInDB):
    pass
