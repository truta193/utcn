using System;
using System.IO;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Data.Core;
using Avalonia.Data.Core.Plugins;
using System.Linq;
using Avalonia.Markup.Xaml;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using PerfumeAppMVVM.Models.Repositories;
using PerfumeAppMVVM.ViewModels;
using PerfumeAppMVVM.Views;

namespace PerfumeAppMVVM;

public partial class App : Application
{
    public static IServiceProvider Services { get; private set; }
    
    public override void Initialize()
    {
        AvaloniaXamlLoader.Load(this);
    }

    public override void OnFrameworkInitializationCompleted()
    {
        var services = new ServiceCollection();
        services.AddDbContext<DatabaseContext>(options => 
            options.UseSqlite($"Data Source={Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "perfumery.db")}"));
        
        services.AddScoped<PerfumeRepository>();
        services.AddScoped<PerfumeryRepository>();
        services.AddScoped<InventoryRepository>();
            
        // Register ViewModel
        services.AddTransient<PerfumeListViewModel>();
            
        // Build the service provider
        Services = services.BuildServiceProvider();

        // Ensure database created
        using (var scope = Services.CreateScope())
        {
            var dbContext = scope.ServiceProvider.GetRequiredService<DatabaseContext>();
            dbContext.Database.EnsureCreated();
        }
        
        if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
        {
            var mainWindow = new MainWindow();
            var perfumeRepository = Services.GetRequiredService<PerfumeRepository>();
            var perfumeryRepository = Services.GetRequiredService<PerfumeryRepository>();
            var inventoryRepository = Services.GetRequiredService<InventoryRepository>();
            var mainWindowViewModel = new MainWindowViewModel(
                perfumeRepository,
                perfumeryRepository,
                inventoryRepository,
                mainWindow
            );
            // Avoid duplicate validations from both Avalonia and the CommunityToolkit. 
            // More info: https://docs.avaloniaui.net/docs/guides/development-guides/data-validation#manage-validationplugins
            DisableAvaloniaDataAnnotationValidation();
            mainWindow.DataContext = mainWindowViewModel;
                
            // Set as the main window
            desktop.MainWindow = mainWindow;
        }
        
        base.OnFrameworkInitializationCompleted();
    }

    private void DisableAvaloniaDataAnnotationValidation()
    {
        // Get an array of plugins to remove
        var dataValidationPluginsToRemove =
            BindingPlugins.DataValidators.OfType<DataAnnotationsValidationPlugin>().ToArray();

        // remove each entry found
        foreach (var plugin in dataValidationPluginsToRemove)
        {
            BindingPlugins.DataValidators.Remove(plugin);
        }
    }
}