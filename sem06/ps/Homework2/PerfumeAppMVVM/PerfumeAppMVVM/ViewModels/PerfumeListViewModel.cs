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

public partial class PerfumeListViewModel : ObservableObject
{
    private readonly PerfumeRepository _perfumeRepository;
    private readonly DialogService _dialogService;

    [ObservableProperty] private ObservableCollection<Perfume> _perfumeList;

    [ObservableProperty] private Perfume _selectedPerfume;

    [ObservableProperty] private string _searchQuery = string.Empty;

    public event EventHandler<Perfume> EditPerfumeRequested;

    public PerfumeListViewModel(PerfumeRepository perfumeRepository, DialogService dialogService)
    {
        _perfumeRepository = perfumeRepository;
        _dialogService = dialogService;

        LoadPerfumesAsync();
    }

    private async void LoadPerfumesAsync()
    {
        Console.WriteLine("Loading perfumes...");
        await SearchPerfumesAsync();
    }

    [RelayCommand]
    private async Task SearchPerfumesAsync()
    {
        try
        {
            var perfumes = string.IsNullOrWhiteSpace(SearchQuery)
                ? await _perfumeRepository.GetAllAsync(sortBy: "Name")
                : await _perfumeRepository.SearchByNameAsync(SearchQuery);

            await Dispatcher.UIThread.InvokeAsync(() =>
            {
                PerfumeList = new ObservableCollection<Perfume>(perfumes);
                SelectedPerfume = null;
            });
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading perfumes: {ex.Message}");
        }
    }

    [RelayCommand]
    private async Task DeletePerfumeAsync()
    {
        if (SelectedPerfume == null)
            return;

        try
        {
            bool result = await _perfumeRepository.DeleteAsync(SelectedPerfume.Id);
            if (result)
            {
                await SearchPerfumesAsync();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error deleting perfume: {ex.Message}");
        }
    }

    [RelayCommand]
    private void EditPerfume()
    {
        if (SelectedPerfume == null)
            return;

        // Raise event to notify parent ViewModel
        EditPerfumeRequested?.Invoke(this, SelectedPerfume);
    }

    [RelayCommand]
    private async Task ViewDetailsAsync()
    {
        if (SelectedPerfume == null)
            return;

        await _dialogService.ShowPerfumeDetailsAsync(SelectedPerfume);
    }

    public async Task RefreshListAsync()
    {
        await SearchPerfumesAsync();
    }
}