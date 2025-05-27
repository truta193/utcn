using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Platform.Storage;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using PerfumeAppMVVM.Models;
using PerfumeAppMVVM.Models.Repositories;

namespace PerfumeAppMVVM.ViewModels;

public partial class PerfumeManagementViewModel : ObservableObject
{
    private readonly PerfumeRepository _perfumeRepository;
    private readonly Window _mainWindow;
    private bool _isEditing = false;

    [ObservableProperty] private Perfume _currentPerfume;

    [ObservableProperty] private string _operationTitle = "Add New Perfume";

    [ObservableProperty] private ObservableCollection<string> _availableConcentrations;

    [ObservableProperty] private ObservableCollection<string> _availableGenders;

    [ObservableProperty] private string _statusMessage;

    [ObservableProperty] private string _imagePath;

    // Assets directory path
    private string AssetsDirectory => Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets");

    public PerfumeManagementViewModel(PerfumeRepository perfumeRepository, Window mainWindow)
    {
        _perfumeRepository = perfumeRepository;
        _mainWindow = mainWindow;

        AvailableConcentrations = new ObservableCollection<string>
        {
            "Eau de Cologne (EdC)",
            "Eau de Toilette (EdT)",
            "Eau de Parfum (EdP)",
            "Parfum",
            "Eau Fraiche"
        };

        AvailableGenders = new ObservableCollection<string>
        {
            "Men",
            "Women",
            "Unisex"
        };

        if (!Directory.Exists(AssetsDirectory))
        {
            Directory.CreateDirectory(AssetsDirectory);
        }

        ResetForm();
    }

    public void SetEditMode(Perfume perfume)
    {
        _isEditing = true;
        OperationTitle = "Edit Perfume";
        CurrentPerfume = new Perfume
        {
            Id = perfume.Id,
            Name = perfume.Name,
            Brand = perfume.Brand,
            Price = perfume.Price,
            Description = perfume.Description,
            VolumeML = perfume.VolumeML,
            Concentration = perfume.Concentration,
            Gender = perfume.Gender,
            ImagePath = perfume.ImagePath
        };

        ImagePath = perfume.ImagePath;
    }

    [RelayCommand]
    public void ResetForm()
    {
        _isEditing = false;
        OperationTitle = "Add New Perfume";
        CurrentPerfume = new Perfume
        {
            Name = string.Empty,
            Brand = string.Empty,
            Price = 0,
            Description = string.Empty,
            VolumeML = 50,
            Concentration = AvailableConcentrations.FirstOrDefault(),
            Gender = AvailableGenders.FirstOrDefault(),
            ImagePath = string.Empty
        };

        ImagePath = string.Empty;
        StatusMessage = string.Empty;
    }

    [RelayCommand]
    private async Task SavePerfumeAsync()
    {
        try
        {
            StatusMessage = string.Empty;

            if (string.IsNullOrWhiteSpace(CurrentPerfume.Name))
            {
                StatusMessage = "Name is required";
                return;
            }

            if (string.IsNullOrWhiteSpace(CurrentPerfume.Brand))
            {
                StatusMessage = "Brand is required";
                return;
            }

            if (CurrentPerfume.Price <= 0)
            {
                StatusMessage = "Price must be greater than 0";
                return;
            }

            CurrentPerfume.ImagePath = ImagePath;

            if (_isEditing)
            {
                var updates = new Dictionary<string, object>
                {
                    { "Name", CurrentPerfume.Name },
                    { "Brand", CurrentPerfume.Brand },
                    { "Description", CurrentPerfume.Description },
                    { "Price", CurrentPerfume.Price },
                    { "VolumeML", CurrentPerfume.VolumeML },
                    { "Concentration", CurrentPerfume.Concentration },
                    { "Gender", CurrentPerfume.Gender },
                    { "ImagePath", CurrentPerfume.ImagePath }
                };

                var updatedPerfume = await _perfumeRepository.UpdateAsync(CurrentPerfume.Id, updates);
                if (updatedPerfume != null)
                {
                    StatusMessage = "Perfume updated successfully!";
                    await Task.Delay(2000);
                    ResetForm();
                }
                else
                {
                    StatusMessage = "Failed to update perfume.";
                }
            }
            else
            {
                var newPerfume = await _perfumeRepository.CreateAsync(
                    CurrentPerfume.Name,
                    CurrentPerfume.Brand,
                    CurrentPerfume.Price,
                    CurrentPerfume.Description,
                    CurrentPerfume.VolumeML,
                    CurrentPerfume.Concentration,
                    CurrentPerfume.Gender,
                    CurrentPerfume.ImagePath
                );

                if (newPerfume != null)
                {
                    StatusMessage = "Perfume added successfully!";
                    await Task.Delay(2000);
                    ResetForm();
                }
                else
                {
                    StatusMessage = "Failed to add perfume.";
                }
            }
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error: {ex.Message}";
        }
    }

    [RelayCommand]
    private async Task SelectImageAsync()
    {
        try
        {
            var storageProvider = _mainWindow.StorageProvider;
            var result = await storageProvider.OpenFilePickerAsync(new FilePickerOpenOptions
            {
                Title = "Select Perfume Image",
                AllowMultiple = false,
                FileTypeFilter = new[]
                {
                    new FilePickerFileType("Image Files")
                    {
                        Patterns = new[] { "*.jpg", "*.jpeg", "*.png", "*.gif", "*.bmp" }
                    }
                }
            });

            var file = result.FirstOrDefault();
            if (file != null)
            {
                string fileName = Path.GetFileName(file.Name);

                string fullPath = Path.Combine(AssetsDirectory, fileName);

                using (var sourceStream = await file.OpenReadAsync())
                using (var fileStream = File.Create(fullPath))
                {
                    await sourceStream.CopyToAsync(fileStream);
                }

                ImagePath = $"/Assets/{fileName}";
            }
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error selecting image: {ex.Message}";
        }
    }
}