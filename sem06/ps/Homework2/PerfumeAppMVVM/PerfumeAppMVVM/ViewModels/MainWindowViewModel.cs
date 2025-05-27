using Avalonia.Controls;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;
using PerfumeAppMVVM.Services;
using System;

namespace PerfumeAppMVVM.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    private readonly Window _mainWindow;
    private readonly DialogService _dialogService;

    [ObservableProperty] private PerfumeListViewModel _perfumeListViewModel;

    [ObservableProperty] private PerfumeryListViewModel _perfumeryListViewModel;

    [ObservableProperty] private PerfumeManagementViewModel _perfumeManagementViewModel;

    [ObservableProperty] private PerfumeryManagementViewModel _perfumeryManagementViewModel;

    [ObservableProperty] private int _selectedTabIndex = 0;

    public MainWindowViewModel(
        PerfumeRepository perfumeRepository,
        PerfumeryRepository perfumeryRepository,
        InventoryRepository inventoryRepository,
        Window mainWindow)
    {
        _mainWindow = mainWindow;

        _dialogService = new DialogService(
            mainWindow,
            inventoryRepository,
            perfumeryRepository,
            perfumeRepository);

        // Subscribe to dialog service events
        _dialogService.ManagePerfumeryInventoryRequested += OnManagePerfumeryInventoryRequested;

        PerfumeManagementViewModel = new PerfumeManagementViewModel(perfumeRepository, mainWindow);
        PerfumeryManagementViewModel = new PerfumeryManagementViewModel(
            perfumeryRepository,
            perfumeRepository,
            inventoryRepository,
            mainWindow);

        PerfumeListViewModel = new PerfumeListViewModel(perfumeRepository, _dialogService);
        PerfumeryListViewModel = new PerfumeryListViewModel(
            perfumeryRepository,
            inventoryRepository,
            _dialogService);

        // Subscribe to edit events
        PerfumeListViewModel.EditPerfumeRequested += OnEditPerfumeRequested;
        PerfumeryListViewModel.EditPerfumeryRequested += OnEditPerfumeryRequested;

        Console.WriteLine("MainWindowViewModel initialized");
    }

    private void OnEditPerfumeRequested(object sender, Perfume perfume)
    {
        Console.WriteLine($"Edit requested for perfume: {perfume.Name}");

        PerfumeManagementViewModel.SetEditMode(perfume);

        Console.WriteLine($"Switching to perfume management tab (index 2)");
        SelectedTabIndex = 2;
    }

    private void OnEditPerfumeryRequested(object sender, Perfumery perfumery)
    {
        Console.WriteLine($"Edit requested for perfumery: {perfumery.Name}");

        PerfumeryManagementViewModel.SetEditMode(perfumery);

        Console.WriteLine($"Switching to perfumery management tab (index 3)");
        SelectedTabIndex = 3;
    }

    private void OnManagePerfumeryInventoryRequested(object sender, Perfumery perfumery)
    {
        Console.WriteLine($"Manage inventory requested for perfumery: {perfumery.Name}");

        PerfumeryManagementViewModel.SetEditMode(perfumery);

        Console.WriteLine($"Switching to perfumery management tab (index 3)");
        SelectedTabIndex = 3;
    }

    [RelayCommand]
    private void AddNewPerfume()
    {
        Console.WriteLine("Add new perfume requested");

        PerfumeManagementViewModel.ResetForm();

        Console.WriteLine("Switching to perfume management tab (index 2)");
        SelectedTabIndex = 2;
    }

    [RelayCommand]
    private void AddNewPerfumery()
    {
        Console.WriteLine("Add new perfumery requested");

        PerfumeryManagementViewModel.ResetForm();

        Console.WriteLine("Switching to perfumery management tab (index 3)");
        SelectedTabIndex = 3;
    }
}