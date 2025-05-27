using Microsoft.EntityFrameworkCore;
using PerfumeAppMVVM.Models;

namespace PerfumeAppMVVM;

public class DatabaseContext : DbContext
{
    public DatabaseContext(DbContextOptions<DatabaseContext> options)
        : base(options)
    {
    }

    public DbSet<Perfume> Perfumes { get; set; }
    public DbSet<Perfumery> Perfumeries { get; set; }
    public DbSet<Inventory> Inventories { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        // Configure indexes
        modelBuilder.Entity<Perfume>()
            .HasIndex(p => p.Name);

        modelBuilder.Entity<Perfume>()
            .HasIndex(p => p.Brand);

        // Configure relationships
        modelBuilder.Entity<Inventory>()
            .HasOne(i => i.Perfumery)
            .WithMany(p => p.Inventories)
            .HasForeignKey(i => i.PerfumeryId)
            .OnDelete(DeleteBehavior.Cascade);

        modelBuilder.Entity<Inventory>()
            .HasOne(i => i.Perfume)
            .WithMany(p => p.Inventories)
            .HasForeignKey(i => i.PerfumeId)
            .OnDelete(DeleteBehavior.Cascade);
    }
}