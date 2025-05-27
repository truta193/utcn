using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace PerfumeAppMVVM.Models.Repositories;

public class InventoryRepository
{
    private readonly DatabaseContext _context;

    public InventoryRepository(DatabaseContext context)
    {
        _context = context;
    }

    public async Task<Inventory> CreateAsync(int perfumeryId, int perfumeId, int quantity = 0, bool isAvailable = true)
    {
        var inventory = new Inventory
        {
            PerfumeryId = perfumeryId,
            PerfumeId = perfumeId,
            Quantity = quantity,
            IsAvailable = isAvailable
        };

        _context.Inventories.Add(inventory);
        await _context.SaveChangesAsync();
        return inventory;
    }

    public async Task<Inventory> GetByIdAsync(int inventoryId)
    {
        return await _context.Inventories
            .FirstOrDefaultAsync(i => i.Id == inventoryId);
    }

    public async Task<Inventory> GetByPerfumeryAndPerfumeAsync(int perfumeryId, int perfumeId)
    {
        return await _context.Inventories
            .FirstOrDefaultAsync(i => i.PerfumeryId == perfumeryId && i.PerfumeId == perfumeId);
    }

    public async Task<List<Inventory>> GetAllByPerfumeryAsync(int perfumeryId, int skip = 0, int limit = 100)
    {
        return await _context.Inventories
            .Where(i => i.PerfumeryId == perfumeryId)
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<List<Inventory>> GetAllByPerfumeAsync(int perfumeId, int skip = 0, int limit = 100)
    {
        return await _context.Inventories
            .Where(i => i.PerfumeId == perfumeId)
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<List<Inventory>> GetOutOfStockByPerfumeryAsync(int perfumeryId)
    {
        return await _context.Inventories
            .Where(i => i.PerfumeryId == perfumeryId && i.Quantity == 0)
            .ToListAsync();
    }

    public async Task<List<Inventory>> GetByAvailabilityAsync(int perfumeryId, bool isAvailable)
    {
        return await _context.Inventories
            .Where(i => i.PerfumeryId == perfumeryId && i.IsAvailable == isAvailable)
            .ToListAsync();
    }

    public async Task<int> GetInventoryCountAsync(int perfumeryId)
    {
        return await _context.Inventories
            .CountAsync(i => i.PerfumeryId == perfumeryId);
    }

    public async Task<Inventory> UpdateAsync(int inventoryId, Dictionary<string, object> updates)
    {
        var inventory = await GetByIdAsync(inventoryId);
        if (inventory == null)
            return null;

        foreach (var update in updates)
        {
            switch (update.Key)
            {
                case "Quantity":
                    var quantity = (int)update.Value;
                    inventory.Quantity = quantity;

                    if (quantity > 0)
                        inventory.IsAvailable = true;
                    else if (quantity == 0)
                        inventory.IsAvailable = false;
                    break;
                case "IsAvailable":
                    inventory.IsAvailable = (bool)update.Value;
                    break;
                case "PerfumeryId":
                    inventory.PerfumeryId = (int)update.Value;
                    break;
                case "PerfumeId":
                    inventory.PerfumeId = (int)update.Value;
                    break;
            }
        }

        await _context.SaveChangesAsync();
        return inventory;
    }

    public async Task<bool> DeleteAsync(int inventoryId)
    {
        var inventory = await GetByIdAsync(inventoryId);
        if (inventory == null)
            return false;

        _context.Inventories.Remove(inventory);
        await _context.SaveChangesAsync();
        return true;
    }
}