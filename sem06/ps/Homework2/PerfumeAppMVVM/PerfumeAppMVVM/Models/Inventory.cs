using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace PerfumeAppMVVM.Models;

public class Inventory
{
    [Key] public int Id { get; set; }

    [Required] public int PerfumeryId { get; set; }

    [Required] public int PerfumeId { get; set; }

    public int Quantity { get; set; } = 0;

    public bool IsAvailable { get; set; } = true;

    [ForeignKey("PerfumeryId")] public virtual Perfumery Perfumery { get; set; }

    [ForeignKey("PerfumeId")] public virtual Perfume Perfume { get; set; }

    public override string ToString()
    {
        return $"<Inventory: {Perfume?.Name} at {Perfumery?.Name}>";
    }
}