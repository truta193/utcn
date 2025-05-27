using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Platform.Storage;
using Avalonia.Threading;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;
using DocumentFormat.OpenXml;
using DocumentFormat.OpenXml.Packaging;
using DocumentFormat.OpenXml.Wordprocessing;

namespace PerfumeAppMVVM.ViewModels;

public class InventoryItemViewModel : ObservableObject
{
    public Inventory Inventory { get; }
    public Perfume Perfume { get; }

    public int Id => Inventory.Id;
    public int Quantity => Inventory.Quantity;
    public bool IsAvailable => Inventory.IsAvailable;

    public InventoryItemViewModel(Inventory inventory, Perfume perfume)
    {
        Inventory = inventory;
        Perfume = perfume;
    }
}

public partial class PerfumeryDetailsViewModel : ObservableObject
{
    private readonly InventoryRepository _inventoryRepository;
    private readonly PerfumeRepository _perfumeRepository;
    private readonly Window _mainWindow;

    [ObservableProperty] private Perfumery _perfumery;

    [ObservableProperty] private ObservableCollection<InventoryItemViewModel> _inventoryItems = new();

    [ObservableProperty] private ObservableCollection<InventoryItemViewModel> _filteredInventory;

    [ObservableProperty] private string _searchQuery = string.Empty;

    [ObservableProperty] private bool _hasInventory;

    [ObservableProperty] private int _perfumeCount;

    [ObservableProperty] private ObservableCollection<InventoryItemViewModel> _outOfStockItems = new();

    [ObservableProperty] private int _outOfStockCount;

    [ObservableProperty] private bool _hasOutOfStock;

    public event EventHandler CloseRequested;
    public event EventHandler<Perfumery> ManageInventoryRequested;

    public PerfumeryDetailsViewModel(
        Perfumery perfumery,
        InventoryRepository inventoryRepository,
        PerfumeRepository perfumeRepository,
        Window mainWindow)
    {
        _perfumery = perfumery;
        _inventoryRepository = inventoryRepository;
        _perfumeRepository = perfumeRepository;
        _mainWindow = mainWindow;

        FilteredInventory = new ObservableCollection<InventoryItemViewModel>();

        LoadInventoryAsync();

        this.PropertyChanged += (s, e) =>
        {
            if (e.PropertyName == nameof(SearchQuery))
            {
                FilterInventory();
            }
        };
    }

    private async void LoadInventoryAsync()
    {
        try
        {
            var inventories = await _inventoryRepository.GetAllByPerfumeryAsync(Perfumery.Id);

            InventoryItems.Clear();
            OutOfStockItems.Clear();

            foreach (var inventory in inventories)
            {
                var perfume = await _perfumeRepository.GetByIdAsync(inventory.PerfumeId);

                if (perfume != null)
                {
                    var item = new InventoryItemViewModel(inventory, perfume);
                    InventoryItems.Add(item);

                    if (inventory.Quantity == 0)
                    {
                        OutOfStockItems.Add(item);
                    }
                }
            }

            PerfumeCount = InventoryItems.Count;
            OutOfStockCount = OutOfStockItems.Count;
            HasInventory = InventoryItems.Count > 0;
            HasOutOfStock = OutOfStockItems.Count > 0;

            FilterInventory();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading inventory: {ex.Message}");
        }
    }

    private void FilterInventory()
    {
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            FilteredInventory.Clear();

            var query = SearchQuery?.ToLower() ?? string.Empty;

            var filtered = string.IsNullOrWhiteSpace(query)
                ? InventoryItems
                : new ObservableCollection<InventoryItemViewModel>(
                    InventoryItems.Where(i =>
                        i.Perfume.Name.ToLower().Contains(query) ||
                        i.Perfume.Brand.ToLower().Contains(query)));

            foreach (var item in filtered)
            {
                FilteredInventory.Add(item);
            }

            HasInventory = FilteredInventory.Count > 0;
        });
    }

    [RelayCommand]
    private void Close()
    {
        CloseRequested?.Invoke(this, EventArgs.Empty);
    }

    [RelayCommand]
    private void ManageInventory()
    {
        ManageInventoryRequested?.Invoke(this, Perfumery);
        CloseRequested?.Invoke(this, EventArgs.Empty);
    }

    [RelayCommand]
    private async Task ExportToCsv()
    {
        try
        {
            if (!HasOutOfStock)
            {
                return;
            }

            var storageProvider = _mainWindow.StorageProvider;
            var saveOptions = new FilePickerSaveOptions
            {
                Title = "Save Out-of-Stock List as CSV",
                SuggestedFileName = $"{Perfumery.Name}_OutOfStock_{DateTime.Now:yyyyMMdd}.csv",
                DefaultExtension = ".csv"
            };

            var file = await storageProvider.SaveFilePickerAsync(saveOptions);
            if (file == null)
                return;

            await GenerateAndSaveCsvAsync(file);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error exporting CSV: {ex.Message}");
        }
    }

    [RelayCommand]
    private async Task ExportToDocx()
    {
        try
        {
            if (!HasOutOfStock)
            {
                return;
            }

            var storageProvider = _mainWindow.StorageProvider;
            var saveOptions = new FilePickerSaveOptions
            {
                Title = "Save Out-of-Stock List as DOCX",
                SuggestedFileName = $"{Perfumery.Name}_OutOfStock_{DateTime.Now:yyyyMMdd}.docx",
                DefaultExtension = ".docx"
            };

            var file = await storageProvider.SaveFilePickerAsync(saveOptions);
            if (file == null)
                return;

            await GenerateAndSaveDocxAsync(file);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error exporting DOCX: {ex.Message}");
        }
    }

    private async Task GenerateAndSaveCsvAsync(IStorageFile file)
    {
        var csvBuilder = new StringBuilder();

        csvBuilder.AppendLine("ID,Name,Brand,Price,Volume,Concentration,Gender");

        foreach (var item in OutOfStockItems)
        {
            csvBuilder.AppendLine(
                $"{item.Perfume.Id}," +
                $"\"{item.Perfume.Name.Replace("\"", "\"\"")}\"," +
                $"\"{item.Perfume.Brand.Replace("\"", "\"\"")}\"," +
                $"{item.Perfume.Price}," +
                $"{item.Perfume.VolumeML}," +
                $"\"{item.Perfume.Concentration?.Replace("\"", "\"\"") ?? ""}\"," +
                $"\"{item.Perfume.Gender?.Replace("\"", "\"\"") ?? ""}\""
            );
        }

        await using var stream = await file.OpenWriteAsync();
        using var writer = new StreamWriter(stream);
        await writer.WriteAsync(csvBuilder.ToString());
    }

    private async Task GenerateAndSaveDocxAsync(IStorageFile file)
    {
        string tempFilePath = Path.Combine(
            Path.GetTempPath(),
            $"OutOfStock_{Guid.NewGuid()}.docx");

        try
        {
            using (WordprocessingDocument wordDocument =
                   WordprocessingDocument.Create(tempFilePath, WordprocessingDocumentType.Document))
            {
                MainDocumentPart mainPart = wordDocument.AddMainDocumentPart();
                mainPart.Document = new Document();
                Body body = mainPart.Document.AppendChild(new Body());

                body.AppendChild(new Paragraph(
                    new Run(
                        new Text($"Out-of-Stock Perfumes - {Perfumery.Name}"))));

                body.AppendChild(new Paragraph(
                    new Run(
                        new Text($"Generated: {DateTime.Now:yyyy-MM-dd}"))));

                body.AppendChild(new Paragraph());

                Table table = new Table();

                TableRow headerRow = new TableRow();
                string[] headers = { "ID", "Name", "Brand", "Price", "Volume", "Concentration", "Gender" };

                foreach (var header in headers)
                {
                    headerRow.AppendChild(new TableCell(
                        new Paragraph(
                            new Run(
                                new Text(header)))));
                }

                table.AppendChild(headerRow);

                foreach (var item in OutOfStockItems)
                {
                    TableRow row = new TableRow();

                    row.AppendChild(new TableCell(new Paragraph(new Run(new Text(item.Perfume.Id.ToString())))));
                    row.AppendChild(new TableCell(new Paragraph(new Run(new Text(item.Perfume.Name ?? "")))));
                    row.AppendChild(new TableCell(new Paragraph(new Run(new Text(item.Perfume.Brand ?? "")))));
                    row.AppendChild(new TableCell(new Paragraph(new Run(new Text($"{item.Perfume.Price:C}")))));
                    row.AppendChild(new TableCell(new Paragraph(
                        new Run(new Text(item.Perfume.VolumeML.HasValue ? $"{item.Perfume.VolumeML} ml" : "")))));
                    row.AppendChild(new TableCell(new Paragraph(new Run(new Text(item.Perfume.Concentration ?? "")))));
                    row.AppendChild(new TableCell(new Paragraph(new Run(new Text(item.Perfume.Gender ?? "")))));

                    table.AppendChild(row);
                }

                body.AppendChild(table);

                body.AppendChild(new Paragraph());
                body.AppendChild(new Paragraph(
                    new Run(
                        new Text($"Total: {OutOfStockItems.Count} items"))));

                mainPart.Document.Save();
            }

            using (var sourceStream = File.OpenRead(tempFilePath))
            using (var targetStream = await file.OpenWriteAsync())
            {
                await sourceStream.CopyToAsync(targetStream);
            }
        }
        finally
        {
            if (File.Exists(tempFilePath))
            {
                try
                {
                    File.Delete(tempFilePath);
                }
                catch
                {
                    /* Ignore cleanup errors */
                }
            }
        }
    }
}