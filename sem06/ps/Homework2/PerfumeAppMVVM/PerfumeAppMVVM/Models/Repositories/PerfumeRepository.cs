using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace PerfumeAppMVVM.Models.Repositories;

public class PerfumeRepository
{
    private readonly DatabaseContext _context;

    public PerfumeRepository(DatabaseContext context)
    {
        _context = context;
    }

    public async Task<Perfume> CreateAsync(string name, string brand, float price, string description = null,
        int? volumeMl = null, string concentration = null, string gender = null, string imagePath = null)
    {
        var perfume = new Perfume
        {
            Name = name,
            Brand = brand,
            Price = price,
            Description = description,
            VolumeML = volumeMl,
            Concentration = concentration,
            Gender = gender,
            ImagePath = imagePath
        };

        _context.Perfumes.Add(perfume);
        await _context.SaveChangesAsync();
        return perfume;
    }

    public async Task<Perfume> GetByIdAsync(int perfumeId)
    {
        return await _context.Perfumes
            .FirstOrDefaultAsync(p => p.Id == perfumeId);
    }

    public async Task<List<Perfume>> GetAllAsync(int skip = 0, int limit = 100, string sortBy = "Name",
        bool sortDesc = false)
    {
        IQueryable<Perfume> query = _context.Perfumes;

        switch (sortBy)
        {
            case "Name":
                query = sortDesc
                    ? query.OrderByDescending(p => p.Name)
                    : query.OrderBy(p => p.Name);
                break;
            case "Brand":
                query = sortDesc
                    ? query.OrderByDescending(p => p.Brand)
                    : query.OrderBy(p => p.Brand);
                break;
            case "Price":
                query = sortDesc
                    ? query.OrderByDescending(p => p.Price)
                    : query.OrderBy(p => p.Price);
                break;
        }

        return await query
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<List<Perfume>> FilterByBrandAsync(string brand, int skip = 0, int limit = 100)
    {
        return await _context.Perfumes
            .Where(p => EF.Functions.Like(p.Brand, $"%{brand}%"))
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<List<Perfume>> SearchByNameAsync(string name, int skip = 0, int limit = 100)
    {
        return await _context.Perfumes
            .Where(p => EF.Functions.Like(p.Name, $"%{name}%"))
            .Skip(skip)
            .Take(limit)
            .ToListAsync();
    }

    public async Task<Perfume> UpdateAsync(int perfumeId, Dictionary<string, object> updates)
    {
        var perfume = await GetByIdAsync(perfumeId);
        if (perfume == null)
            return null;

        foreach (var update in updates)
        {
            switch (update.Key)
            {
                case "Name":
                    perfume.Name = (string)update.Value;
                    break;
                case "Brand":
                    perfume.Brand = (string)update.Value;
                    break;
                case "Description":
                    perfume.Description = (string)update.Value;
                    break;
                case "Price":
                    perfume.Price = (float)update.Value;
                    break;
                case "VolumeML":
                    perfume.VolumeML = (int?)update.Value;
                    break;
                case "Concentration":
                    perfume.Concentration = (string)update.Value;
                    break;
                case "Gender":
                    perfume.Gender = (string)update.Value;
                    break;
                case "ImagePath":
                    perfume.ImagePath = (string)update.Value;
                    break;
            }
        }

        await _context.SaveChangesAsync();
        return perfume;
    }

    public async Task<bool> DeleteAsync(int perfumeId)
    {
        var perfume = await GetByIdAsync(perfumeId);
        if (perfume == null)
            return false;

        _context.Perfumes.Remove(perfume);
        await _context.SaveChangesAsync();
        return true;
    }
}