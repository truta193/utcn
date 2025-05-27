using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using Avalonia.Threading;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;
using PerfumeAppMVVM.Services;

namespace PerfumeAppMVVM.ViewModels;

public partial class PerfumeryListViewModel : ObservableObject
{
    private readonly PerfumeryRepository _perfumeryRepository;
    private readonly InventoryRepository _inventoryRepository;
    private readonly DialogService _dialogService;

    [ObservableProperty] private ObservableCollection<PerfumeryViewModel> _perfumeryList;

    [ObservableProperty] private PerfumeryViewModel _selectedPerfumery;

    [ObservableProperty] private string _searchQuery = string.Empty;

    public event EventHandler<Perfumery> EditPerfumeryRequested;

    public PerfumeryListViewModel(
        PerfumeryRepository perfumeryRepository,
        InventoryRepository inventoryRepository,
        DialogService dialogService)
    {
        _perfumeryRepository = perfumeryRepository;
        _inventoryRepository = inventoryRepository;
        _dialogService = dialogService;

        LoadPerfumeriesAsync();
    }

    private async void LoadPerfumeriesAsync()
    {
        Console.WriteLine("Loading perfumeries...");
        await SearchPerfumeriesAsync();
    }

    [RelayCommand]
    private async Task SearchPerfumeriesAsync()
    {
        try
        {
            var perfumeries = string.IsNullOrWhiteSpace(SearchQuery)
                ? await _perfumeryRepository.GetAllAsync()
                : await _perfumeryRepository.SearchByNameAsync(SearchQuery);

            var viewModels = new ObservableCollection<PerfumeryViewModel>();

            foreach (var perfumery in perfumeries)
            {
                var inventoryCount = await _inventoryRepository.GetInventoryCountAsync(perfumery.Id);
                viewModels.Add(new PerfumeryViewModel(perfumery, inventoryCount));
            }

            await Dispatcher.UIThread.InvokeAsync(() =>
            {
                PerfumeryList = viewModels;
                SelectedPerfumery = null;
            });
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading perfumeries: {ex.Message}");
        }
    }

    [RelayCommand]
    private async Task DeletePerfumeryAsync()
    {
        if (SelectedPerfumery == null)
            return;

        try
        {
            bool result = await _perfumeryRepository.DeleteAsync(SelectedPerfumery.Id);
            if (result)
            {
                await SearchPerfumeriesAsync();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error deleting perfumery: {ex.Message}");
        }
    }

    [RelayCommand]
    private void EditPerfumery()
    {
        if (SelectedPerfumery == null)
            return;

        // Raise event to notify parent ViewModel
        EditPerfumeryRequested?.Invoke(this, SelectedPerfumery.Perfumery);
    }

    [RelayCommand]
    private async Task ViewDetailsAsync()
    {
        if (SelectedPerfumery == null)
            return;

        await _dialogService.ShowPerfumeryDetailsAsync(SelectedPerfumery.Perfumery);
    }

    public async Task RefreshListAsync()
    {
        await SearchPerfumeriesAsync();
    }
}

public partial class PerfumeryViewModel : ObservableObject
{
    public Perfumery Perfumery { get; }

    public int Id => Perfumery.Id;
    public string Name => Perfumery.Name;
    public string City => Perfumery.City;
    public string Address => Perfumery.Address;
    public string Phone => Perfumery.Phone;
    public string Email => Perfumery.Email;
    public string ManagerName => Perfumery.ManagerName;

    [ObservableProperty] private int _inventoryCount;

    public PerfumeryViewModel(Perfumery perfumery, int inventoryCount)
    {
        Perfumery = perfumery;
        InventoryCount = inventoryCount;
    }
}