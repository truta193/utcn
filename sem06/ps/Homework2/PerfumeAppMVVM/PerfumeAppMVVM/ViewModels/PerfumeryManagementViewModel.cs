using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Threading;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;

namespace PerfumeAppMVVM.ViewModels;

public partial class PerfumeInventoryViewModel : ObservableObject
{
    public Perfume Perfume { get; }

    [ObservableProperty] private bool _isInInventory;

    [ObservableProperty] private int _inventoryQuantity;

    [ObservableProperty] private int? _inventoryId;

    public int Id => Perfume.Id;
    public string Name => Perfume.Name;
    public string Brand => Perfume.Brand;
    public float Price => Perfume.Price;
    public string ImagePath => Perfume.ImagePath;

    public PerfumeInventoryViewModel(Perfume perfume, int quantity = 0, int? inventoryId = null)
    {
        Perfume = perfume;
        InventoryQuantity = quantity;
        IsInInventory = quantity > 0;
        InventoryId = inventoryId;
    }
}

public partial class PerfumeryManagementViewModel : ObservableObject
{
    private readonly PerfumeryRepository _perfumeryRepository;
    private readonly PerfumeRepository _perfumeRepository;
    private readonly InventoryRepository _inventoryRepository;
    private readonly Window _mainWindow;
    private bool _isEditing = false;

    [ObservableProperty] private Perfumery _currentPerfumery;

    [ObservableProperty] private string _operationTitle = "Add New Perfumery";

    [ObservableProperty] private string _statusMessage;

    [ObservableProperty] private bool _isEditMode;

    [ObservableProperty] private ObservableCollection<PerfumeInventoryViewModel> _inventoryItems = new();

    [ObservableProperty] private ObservableCollection<PerfumeInventoryViewModel> _filteredInventory;

    [ObservableProperty] private PerfumeInventoryViewModel _selectedInventoryItem;

    [ObservableProperty] private string _inventorySearchQuery = string.Empty;

    [ObservableProperty] private int _quantityToUpdate = 1;

    [ObservableProperty] private bool _isAddPerfumeVisible = false;

    [ObservableProperty] private string _perfumeSearchQuery = string.Empty;

    [ObservableProperty] private ObservableCollection<PerfumeInventoryViewModel> _searchResults = new();

    [ObservableProperty] private PerfumeInventoryViewModel _selectedSearchResult;

    [ObservableProperty] private int _quantityToAdd = 1;

    public PerfumeryManagementViewModel(
        PerfumeryRepository perfumeryRepository,
        PerfumeRepository perfumeRepository,
        InventoryRepository inventoryRepository,
        Window mainWindow)
    {
        _perfumeryRepository = perfumeryRepository;
        _perfumeRepository = perfumeRepository;
        _inventoryRepository = inventoryRepository;
        _mainWindow = mainWindow;

        FilteredInventory = new ObservableCollection<PerfumeInventoryViewModel>();

        ResetForm();

        this.PropertyChanged += (s, e) =>
        {
            if (e.PropertyName == nameof(InventorySearchQuery))
            {
                FilterInventory();
            }
            else if (e.PropertyName == nameof(PerfumeSearchQuery) && IsAddPerfumeVisible)
            {
                SearchPerfumes();
            }
            else if (e.PropertyName == nameof(SelectedInventoryItem))
            {
                // Reset quantity to current item's quantity when selecting an item
                if (SelectedInventoryItem != null)
                {
                    QuantityToUpdate = SelectedInventoryItem.InventoryQuantity;
                }
            }
        };
    }

    public void SetEditMode(Perfumery perfumery)
    {
        _isEditing = true;
        IsEditMode = true;
        OperationTitle = "Edit Perfumery";
        CurrentPerfumery = new Perfumery
        {
            Id = perfumery.Id,
            Name = perfumery.Name,
            Address = perfumery.Address,
            City = perfumery.City,
            Phone = perfumery.Phone,
            Email = perfumery.Email,
            ManagerName = perfumery.ManagerName
        };

        LoadInventory();
    }

    [RelayCommand]
    public void ResetForm()
    {
        _isEditing = false;
        IsEditMode = false;
        OperationTitle = "Add New Perfumery";
        CurrentPerfumery = new Perfumery
        {
            Name = string.Empty,
            Address = string.Empty,
            City = string.Empty,
            Phone = string.Empty,
            Email = string.Empty,
            ManagerName = string.Empty
        };

        StatusMessage = string.Empty;
        InventoryItems.Clear();
        FilteredInventory.Clear();
        SelectedInventoryItem = null;

        IsAddPerfumeVisible = false;
        SearchResults.Clear();
    }

    [RelayCommand]
    private async Task SavePerfumeryAsync()
    {
        try
        {
            StatusMessage = string.Empty;

            if (string.IsNullOrWhiteSpace(CurrentPerfumery.Name))
            {
                StatusMessage = "Name is required";
                return;
            }

            if (string.IsNullOrWhiteSpace(CurrentPerfumery.City))
            {
                StatusMessage = "City is required";
                return;
            }

            if (string.IsNullOrWhiteSpace(CurrentPerfumery.Address))
            {
                StatusMessage = "Address is required";
                return;
            }

            if (_isEditing)
            {
                var updates = new Dictionary<string, object>
                {
                    { "Name", CurrentPerfumery.Name },
                    { "Address", CurrentPerfumery.Address },
                    { "City", CurrentPerfumery.City },
                    { "Phone", CurrentPerfumery.Phone },
                    { "Email", CurrentPerfumery.Email },
                    { "ManagerName", CurrentPerfumery.ManagerName }
                };

                var updatedPerfumery = await _perfumeryRepository.UpdateAsync(CurrentPerfumery.Id, updates);
                if (updatedPerfumery != null)
                {
                    StatusMessage = "Perfumery updated successfully!";
                    IsEditMode = true;
                    if (InventoryItems.Count == 0)
                    {
                        LoadInventory();
                    }
                }
                else
                {
                    StatusMessage = "Failed to update perfumery.";
                }
            }
            else
            {
                var newPerfumery = await _perfumeryRepository.CreateAsync(
                    CurrentPerfumery.Name,
                    CurrentPerfumery.Address,
                    CurrentPerfumery.City,
                    CurrentPerfumery.Phone,
                    CurrentPerfumery.Email,
                    CurrentPerfumery.ManagerName
                );

                if (newPerfumery != null)
                {
                    StatusMessage = "Perfumery added successfully!";
                    CurrentPerfumery = newPerfumery;
                    _isEditing = true;
                    IsEditMode = true;
                }
                else
                {
                    StatusMessage = "Failed to add perfumery.";
                }
            }
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error: {ex.Message}";
            Console.WriteLine($"Error saving perfumery: {ex.Message}");
        }
    }

    private async void LoadInventory()
    {
        try
        {
            var inventories = await _inventoryRepository.GetAllByPerfumeryAsync(CurrentPerfumery.Id);

            InventoryItems.Clear();

            foreach (var inventory in inventories)
            {
                var perfume = await _perfumeRepository.GetByIdAsync(inventory.PerfumeId);
                if (perfume != null)
                {
                    InventoryItems.Add(new PerfumeInventoryViewModel(
                        perfume,
                        inventory.Quantity,
                        inventory.Id));
                }
            }

            FilterInventory();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading inventory: {ex.Message}");
            StatusMessage = $"Error loading inventory: {ex.Message}";
        }
    }

    private void FilterInventory()
    {
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            FilteredInventory.Clear();

            var query = InventorySearchQuery?.ToLower() ?? string.Empty;

            var filtered = string.IsNullOrWhiteSpace(query)
                ? InventoryItems
                : new ObservableCollection<PerfumeInventoryViewModel>(
                    InventoryItems.Where(p =>
                        p.Name.ToLower().Contains(query) ||
                        p.Brand.ToLower().Contains(query)));

            foreach (var item in filtered)
            {
                FilteredInventory.Add(item);
            }
        });
    }

    [RelayCommand]
    private async Task UpdateInventoryItemAsync()
    {
        if (SelectedInventoryItem == null || !IsEditMode)
            return;

        try
        {
            int quantity = QuantityToUpdate;

            if (SelectedInventoryItem.InventoryId.HasValue)
            {
                var updates = new Dictionary<string, object>
                {
                    { "Quantity", quantity }
                };

                var updated = await _inventoryRepository.UpdateAsync(
                    SelectedInventoryItem.InventoryId.Value, updates);

                if (updated != null)
                {
                    SelectedInventoryItem.InventoryQuantity = quantity;
                    SelectedInventoryItem.IsInInventory = quantity > 0;

                    StatusMessage = $"Updated inventory quantity for {SelectedInventoryItem.Name}";
                }
            }
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error updating inventory: {ex.Message}";
            Console.WriteLine($"Error updating inventory: {ex.Message}");
        }
    }

    [RelayCommand]
    private void ShowAddPerfume()
    {
        if (!IsEditMode)
            return;

        IsAddPerfumeVisible = true;
        PerfumeSearchQuery = string.Empty;
        SearchResults.Clear();
        SelectedSearchResult = null;
        QuantityToAdd = 1;
    }

    [RelayCommand]
    private void CancelAddPerfume()
    {
        IsAddPerfumeVisible = false;
        SearchResults.Clear();
    }

    private async void SearchPerfumes()
    {
        try
        {
            if (string.IsNullOrWhiteSpace(PerfumeSearchQuery) || PerfumeSearchQuery.Length < 2)
            {
                SearchResults.Clear();
                return;
            }

            var query = PerfumeSearchQuery.ToLower();
            var perfumes = await _perfumeRepository.SearchByNameAsync(query);

            var existingIds = InventoryItems.Select(i => i.Id).ToHashSet();
            var filteredPerfumes = perfumes.Where(p => !existingIds.Contains(p.Id)).ToList();

            Dispatcher.UIThread.InvokeAsync(() =>
            {
                SearchResults.Clear();

                foreach (var perfume in filteredPerfumes)
                {
                    SearchResults.Add(new PerfumeInventoryViewModel(perfume));
                }
            });
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error searching perfumes: {ex.Message}");
        }
    }

    [RelayCommand]
    private async Task AddPerfumeToInventoryAsync()
    {
        if (SelectedSearchResult == null || !IsEditMode)
            return;

        try
        {
            int perfumeId = SelectedSearchResult.Id;
            int quantity = QuantityToAdd;

            var newInventory = await _inventoryRepository.CreateAsync(
                CurrentPerfumery.Id,
                perfumeId,
                quantity,
                quantity > 0
            );

            if (newInventory != null)
            {
                var newItem = new PerfumeInventoryViewModel(
                    SelectedSearchResult.Perfume,
                    quantity,
                    newInventory.Id);

                InventoryItems.Add(newItem);

                FilterInventory();

                StatusMessage = $"Added {SelectedSearchResult.Name} to inventory";

                IsAddPerfumeVisible = false;
            }
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error adding to inventory: {ex.Message}";
            Console.WriteLine($"Error adding to inventory: {ex.Message}");
        }
    }

    [RelayCommand]
    private async Task RemoveFromInventoryAsync()
    {
        if (SelectedInventoryItem == null || !IsEditMode || !SelectedInventoryItem.InventoryId.HasValue)
            return;

        try
        {
            var result = await _inventoryRepository.DeleteAsync(SelectedInventoryItem.InventoryId.Value);

            if (result)
            {
                InventoryItems.Remove(SelectedInventoryItem);
                FilteredInventory.Remove(SelectedInventoryItem);

                StatusMessage = $"Removed {SelectedInventoryItem.Name} from inventory";
                SelectedInventoryItem = null;
            }
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error removing from inventory: {ex.Message}";
            Console.WriteLine($"Error removing from inventory: {ex.Message}");
        }
    }
}