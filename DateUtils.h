#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

class DateUtils {
public:
    // Obtener fecha actual como year_month_day
    static year_month_day today() {
        auto now = system_clock::now();
        auto days = floor<chrono::days>(now);
        return year_month_day{days};
    }

    // Parsear "2024-12-03" → year_month_day
    static year_month_day parseDate(const string& dateStr) {
        istringstream iss{dateStr};
        int y, m, d;
        char delim;
        iss >> y >> delim >> m >> delim >> d;
        
        return year{y} / month{static_cast<unsigned>(m)} / day{static_cast<unsigned>(d)};
    }

    // year_month_day → "2024-12-03"
    static string formatDate(const year_month_day& ymd) {
        ostringstream oss;
        oss << static_cast<int>(ymd.year()) << "-"
            << setfill('0') << setw(2) << static_cast<unsigned>(ymd.month()) << "-"
            << setw(2) << static_cast<unsigned>(ymd.day());
        return oss.str();
    }

    // Días entre dos fechas
    static int daysBetween(const year_month_day& start, const year_month_day& end) {
        auto startDays = sys_days{start};
        auto endDays = sys_days{end};
        return (endDays - startDays).count();
    }

    // Verificar si es la misma fecha
    static bool isSameDate(const year_month_day& d1, const year_month_day& d2) {
        return d1.year() == d2.year() && 
               d1.month() == d2.month() && 
               d1.day() == d2.day();
    }
};

#endif
