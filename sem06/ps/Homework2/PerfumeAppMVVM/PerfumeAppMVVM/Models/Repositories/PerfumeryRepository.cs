using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace PerfumeAppMVVM.Models.Repositories;

public class PerfumeryRepository
{
    private readonly DatabaseContext _context;

    public PerfumeryRepository(DatabaseContext context)
    {
        _context = context;
    }

    public async Task<Perfumery> CreateAsync(string name, string address, string city, string phone = null,
        string email = null, string managerName = null)
    {
        var perfumery = new Perfumery
        {
            Name = name,
            Address = address,
            City = city,
            Phone = phone,
            Email = email,
            ManagerName = managerName
        };

        _context.Perfumeries.Add(perfumery);
        await _context.SaveChangesAsync();
        return perfumery;
    }

    public async Task<Perfumery> GetByIdAsync(int perfumeryId)
    {
        return await _context.Perfumeries
            .FirstOrDefaultAsync(p => p.Id == perfumeryId);
    }

    public async Task<List<Perfumery>> GetAllAsync(int skip = 0, int limit = 100)
    {
        return await _context.Perfumeries
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<List<Perfumery>> SearchByNameAsync(string name, int skip = 0, int limit = 100)
    {
        return await _context.Perfumeries
            .Where(p => EF.Functions.Like(p.Name, $"%{name}%") ||
                        EF.Functions.Like(p.City, $"%{name}%"))
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<Perfumery> UpdateAsync(int perfumeryId, Dictionary<string, object> updates)
    {
        var perfumery = await GetByIdAsync(perfumeryId);
        if (perfumery == null)
            return null;

        foreach (var update in updates)
        {
            switch (update.Key)
            {
                case "Name":
                    perfumery.Name = (string)update.Value;
                    break;
                case "Address":
                    perfumery.Address = (string)update.Value;
                    break;
                case "City":
                    perfumery.City = (string)update.Value;
                    break;
                case "Phone":
                    perfumery.Phone = (string)update.Value;
                    break;
                case "Email":
                    perfumery.Email = (string)update.Value;
                    break;
                case "ManagerName":
                    perfumery.ManagerName = (string)update.Value;
                    break;
            }
        }

        await _context.SaveChangesAsync();
        return perfumery;
    }

    public async Task<bool> DeleteAsync(int perfumeryId)
    {
        var perfumery = await GetByIdAsync(perfumeryId);
        if (perfumery == null)
            return false;

        _context.Perfumeries.Remove(perfumery);
        await _context.SaveChangesAsync();
        return true;
    }
}