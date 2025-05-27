using Avalonia.Data.Converters;
using Avalonia.Media;
using System;
using System.Globalization;

namespace PerfumeAppMVVM.Converters;

public class BoolToColorConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
    {
        if (value is bool isTrue)
        {
            return isTrue
                ? new SolidColorBrush(Color.Parse("#4CAF50"))
                : new SolidColorBrush(Color.Parse("#9E9E9E"));
        }

        return new SolidColorBrush(Color.Parse("#9E9E9E"));
    }

    public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}