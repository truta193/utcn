using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;

namespace PerfumeAppMVVM.ViewModels;

public class InventoryItem
{
    public string PerfumeryName { get; set; }
    public int Quantity { get; set; }
}

public partial class PerfumeDetailsViewModel : ObservableObject
{
    private readonly InventoryRepository _inventoryRepository;
    private readonly PerfumeryRepository _perfumeryRepository;

    [ObservableProperty] private Perfume _perfume;

    [ObservableProperty]
    private ObservableCollection<InventoryItem> _inventoryItems = new ObservableCollection<InventoryItem>();

    [ObservableProperty] private bool _hasInventory;

    public event EventHandler CloseRequested;

    public PerfumeDetailsViewModel(
        Perfume perfume,
        InventoryRepository inventoryRepository,
        PerfumeryRepository perfumeryRepository)
    {
        _perfume = perfume;
        _inventoryRepository = inventoryRepository;
        _perfumeryRepository = perfumeryRepository;

        LoadInventoryAsync();
    }

    private async void LoadInventoryAsync()
    {
        try
        {
            var inventories = await _inventoryRepository.GetAllByPerfumeAsync(Perfume.Id);

            foreach (var inventory in inventories)
            {
                var perfumery = await _perfumeryRepository.GetByIdAsync(inventory.PerfumeryId);

                if (perfumery != null)
                {
                    InventoryItems.Add(new InventoryItem
                    {
                        PerfumeryName = perfumery.Name,
                        Quantity = inventory.Quantity
                    });
                }
            }

            HasInventory = InventoryItems.Count > 0;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading inventory: {ex.Message}");
        }
    }

    [RelayCommand]
    private void Close()
    {
        CloseRequested?.Invoke(this, EventArgs.Empty);
    }
}