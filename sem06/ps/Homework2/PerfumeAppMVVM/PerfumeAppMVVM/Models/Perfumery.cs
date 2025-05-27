using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace PerfumeAppMVVM.Models;

public class Perfumery
{
    [Key] public int Id { get; set; }

    [Required] [MaxLength(100)] public string Name { get; set; }

    [Required] [MaxLength(255)] public string Address { get; set; }

    [Required] [MaxLength(100)] public string City { get; set; }

    [MaxLength(20)] public string Phone { get; set; }

    [MaxLength(100)] public string Email { get; set; }

    [MaxLength(100)] public string ManagerName { get; set; }

    public virtual ICollection<Inventory> Inventories { get; set; }

    public override string ToString()
    {
        return $"<Perfumery {Name} ({City})>";
    }
}