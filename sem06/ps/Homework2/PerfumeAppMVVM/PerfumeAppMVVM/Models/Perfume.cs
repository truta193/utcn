using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace PerfumeAppMVVM.Models;

public class Perfume
{
    [Key] public int Id { get; set; }

    [Required] [MaxLength(100)] public string Name { get; set; }

    [Required] [MaxLength(100)] public string Brand { get; set; }

    public string? Description { get; set; }

    [Required] public float Price { get; set; }

    public int? VolumeML { get; set; }

    [MaxLength(50)] public string Concentration { get; set; }

    [MaxLength(20)] public string Gender { get; set; }

    [MaxLength(255)] public string? ImagePath { get; set; }

    public virtual ICollection<Inventory> Inventories { get; set; }

    public override string ToString()
    {
        return $"<Perfume {Name} by {Brand}>";
    }
}