#include "csv_manager.h"

#include <sys/stat.h>

CSVManager::CSVManager(std::string filePath, std::string *buffer, int numArgs) : m_filePath(filePath), m_numArgs(numArgs)
{
    if(!exists(filePath))
    {
        create(filePath, buffer);
    }
}

auto CSVManager::getNumEntries() -> int
{
    std::fstream fin;
    fin.open(m_filePath,std::ios::in);
    std::string line;
    std::getline(fin, line); //skip title row
    int numLines = 0;
    if(!fin.eof())
    {
        while(std::getline(fin,line))
        {
            numLines++;
        }
    }
    fin.close();
    return numLines;
}

auto CSVManager::exists(std::string &filePath) -> bool
{
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}

void CSVManager::create(std::string filePath, std::string *buffer)
{
    m_filePath = filePath;
    std::fstream fout;
    if(!exists(filePath))
    {
        fout.open(filePath,std::ios::out | std::ios::app);
        for (int i = 0; i < m_numArgs; i++)
        {
            fout << *buffer;
            if(i + 1 < m_numArgs)
            {
                fout << ",";
            }
            buffer ++;
        };
        fout << "\n";
        fout.close();
    }
}

void CSVManager::createRecord(std::string *buffer)
{
    std::fstream fout;
    fout.open(m_filePath,std::ios::out | std::ios::app);
    for (int i = 0; i < m_numArgs - 1; i++)
    {
        fout << *buffer<<",";
        buffer ++;
    };
    fout << *buffer << "\n";
    fout.close();
}

auto CSVManager::readRecord(int rowIndex) -> std::vector<std::string>
{
    // File pointer
    std::fstream fin;
    // Open an existing file
    fin.open(m_filePath, std::ios::in);

    // Read the Data from the file
    // as String Vector
    std::vector<std::string> row;
    std::string line;
    std::string element;

    // read an entire row and
    // store it in a string variable 'line'
    for(int i = 0; i < rowIndex + 1; ++i) // skip first n rows (including title column)
    {
        std::getline(fin, line);
    }

    std::getline(fin, line);
    std::stringstream str_line(line);

    while (std::getline(str_line, element,','))
    {
        row.push_back(element);
    }
    fin.close();
    return row;
}

void CSVManager::updateRecord(int rowIndex, std::string *buffer)
{
    std::fstream fin;
    std::fstream fout;

    std::string newFile = (m_filePath + "new");
    fin.open(m_filePath,std::ios::in);
    fout.open(newFile,std::ios::out | std::ios::app);

    std::string line;
    std::string element;
    std::vector<std::string> row;

    // Traverse the file
    //Add the entries before row <rowIndex> to the placeholder file
    for(int j = 0; j < rowIndex + 1; ++j) // skip first n rows (including title column)
    {
        std::getline(fin, line);
        if (!fin.eof())
        {
            std::stringstream str_line(line);

            while (std::getline(str_line, element,','))
            {
                row.push_back(element);
            }

            for(int i = 0; i < m_numArgs - 1; i++)
            {
                fout << row[i] << ",";
            }

            fout << row[m_numArgs - 1] << "\n";
            row.clear();
            line.clear();
        }
    }

    //Enter the new entry
    if (!fin.eof()) {

        for (int i = 0; i < m_numArgs - 1; i++) {
            fout << *buffer << ",";
            buffer++;
        }

        fout << *buffer << "\n";
    }
    //Throw away the old entry
    if (!fin.eof())
    {
        std::string garbage;
        std::getline(fin, garbage); // throw away old entry
        line.clear();
    }

    //Add the rest of the entries to the placeholder file
    while (!fin.eof()) {
        row.clear();
        std::getline(fin, line);
        if(!fin.eof())
        {
            std::stringstream str_line(line);
            while (std::getline(str_line, element,','))
            {
                row.push_back(element);
            }

            for(int i = 0; i < m_numArgs - 1 && i < row.size(); i++)
            {
                fout << row[i] << ",";
            }

            std::string last = row[m_numArgs - 1];
            fout << last << "\n";
        }
    }

    fin.close();
    fout.close();

    remove( m_filePath.c_str() );

    // renaming the updated file with the existing file name
    rename((newFile).c_str(), (m_filePath).c_str());
}

void CSVManager::deleteRecord(int rowIndex)
{
    std::fstream fin;
    std::fstream fout;

    std::string newFile = (m_filePath + "new");
    fin.open(m_filePath,std::ios::in);
    fout.open(newFile,std::ios::out | std::ios::app);

    std::string line;
    std::string element;
    std::vector<std::string> row;

    //Traverse the file
    //add first n entriees to the placeholder file
    for(int j = 0; j < rowIndex + 1; ++j) // skip first n rows (including title column)
    {
        std::getline(fin, line);

        if (!fin.eof())
        {
            std::stringstream str_line(line);
            while (std::getline(str_line, element,','))
            {
                row.push_back(element);
            }
            for(int i = 0; i < m_numArgs - 1; i++)
            {
                fout << row[i] << ",";
            }
            fout << row[m_numArgs - 1] << "\n";
            row.clear();
            line.clear();
        }
    }

    //Skip the entry at index <rowIndex>
    if (!fin.eof())
    {
        std::string garbage;
        std::getline(fin, garbage); // throw away old entry
        line.clear();
    }

    //Add the rest of the entries to the placeholder file
    while (!fin.eof()) {
        row.clear();
        std::getline(fin, line);
        if(!fin.eof())
        {
            std::stringstream str_line(line);

            while (std::getline(str_line, element,','))
            {
                row.push_back(element);
            }
            for(int i = 0; i < m_numArgs - 1 && i < row.size(); i++)
            {
                fout << row[i] << ",";
            }
            std::string last = row[m_numArgs - 1];
            fout << last << "\n";
        }
    }
    fin.close();
    fout.close();

    remove( m_filePath.c_str() );

    // renaming the updated file with the existing file name
    rename((newFile).c_str(), (m_filePath).c_str());
}
