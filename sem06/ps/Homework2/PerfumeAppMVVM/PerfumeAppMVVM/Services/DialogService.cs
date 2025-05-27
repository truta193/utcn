using System;
using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Platform;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;
using PerfumeAppMVVM.ViewModels;
using PerfumeAppMVVM.Views;

namespace PerfumeAppMVVM.Services;

public class DialogService
{
    private readonly Window _mainWindow;
    private readonly InventoryRepository _inventoryRepository;
    private readonly PerfumeryRepository _perfumeryRepository;
    private readonly PerfumeRepository _perfumeRepository;

    public event EventHandler<Perfumery> ManagePerfumeryInventoryRequested;

    public DialogService(
        Window mainWindow,
        InventoryRepository inventoryRepository,
        PerfumeryRepository perfumeryRepository,
        PerfumeRepository perfumeRepository)
    {
        _mainWindow = mainWindow;
        _inventoryRepository = inventoryRepository;
        _perfumeryRepository = perfumeryRepository;
        _perfumeRepository = perfumeRepository;
    }

    public async Task ShowPerfumeDetailsAsync(Perfume perfume)
    {
        var viewModel = new PerfumeDetailsViewModel(
            perfume,
            _inventoryRepository,
            _perfumeryRepository
        );

        var detailsView = new PerfumeDetailsView
        {
            DataContext = viewModel
        };

        var dialog = new Window
        {
            Content = detailsView,
            SizeToContent = SizeToContent.WidthAndHeight,
            SystemDecorations = SystemDecorations.None,
            WindowStartupLocation = WindowStartupLocation.CenterOwner,
            Background = null,
            TransparencyLevelHint = new[] { WindowTransparencyLevel.Blur, WindowTransparencyLevel.Transparent },
            ExtendClientAreaToDecorationsHint = true,
            ExtendClientAreaChromeHints = ExtendClientAreaChromeHints.NoChrome,
            CanResize = false
        };

        viewModel.CloseRequested += (s, e) => dialog.Close();

        await dialog.ShowDialog(_mainWindow);
    }

    public async Task ShowPerfumeryDetailsAsync(Perfumery perfumery)
    {
        var viewModel = new PerfumeryDetailsViewModel(
            perfumery,
            _inventoryRepository,
            _perfumeRepository,
            _mainWindow // Pass the main window for file picker
        );

        var detailsView = new PerfumeryDetailsView
        {
            DataContext = viewModel
        };

        var dialog = new Window
        {
            Content = detailsView,
            SizeToContent = SizeToContent.WidthAndHeight,
            SystemDecorations = SystemDecorations.None,
            WindowStartupLocation = WindowStartupLocation.CenterOwner,
            Background = null,
            TransparencyLevelHint = new[] { WindowTransparencyLevel.Blur, WindowTransparencyLevel.Transparent },
            ExtendClientAreaToDecorationsHint = true,
            ExtendClientAreaChromeHints = ExtendClientAreaChromeHints.NoChrome,
            CanResize = false
        };

        viewModel.CloseRequested += (s, e) => dialog.Close();
        viewModel.ManageInventoryRequested += (s, e) =>
        {
            dialog.Close();
            ManagePerfumeryInventoryRequested?.Invoke(this, e);
        };

        await dialog.ShowDialog(_mainWindow);
    }
}