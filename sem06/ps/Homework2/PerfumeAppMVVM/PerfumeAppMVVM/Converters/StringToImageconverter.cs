using System;
using System.Globalization;
using System.IO;
using Avalonia.Data.Converters;
using Avalonia.Media.Imaging;

namespace PerfumeAppMVVM.Converters;

public class StringToImageConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
    {
        if (value is string path && !string.IsNullOrEmpty(path))
        {
            try
            {
                // For /Assets/ paths, resolve from base directory
                if (path.StartsWith("/Assets/"))
                {
                    string fullPath = Path.Combine(
                        AppDomain.CurrentDomain.BaseDirectory,
                        path.TrimStart('/'));

                    if (File.Exists(fullPath))
                        return new Bitmap(fullPath);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error converting image path: {ex.Message}");
            }
        }

        return null;
    }

    public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}