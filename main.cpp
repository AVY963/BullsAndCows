#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <time.h>


using namespace std;

//--------------------------------------------------------------------------------------------------
const unsigned int LEN = 4;

//--------------------------------------------------------------------------------------------------
class CowsAndBulls_Player
{
public:
    CowsAndBulls_Player() { fillPool(); }
    void play()
    {
        cout << "Введите случайное число от 1000 до 9999, без повторяющихся цифр:" << endl;
        cin >> answer;
        guess();
    }

private:
    void guess()
    {
        pair<int, int> res; int cc = 1;
        cout << endl << "Загаданное число: " << answer << endl << "==============" << endl;
        cout << "\n|  ПОПЫТКА   |   БЫКИ   | КОРОВЫ  | \n-----------------------------------\n";
        while( true )
        {
            string gs = gimmeANumber();
            if( gs.empty() ) { cout << endl << "Что-то пошло не так." << endl << "Нельзя получить ответ!" << endl; return; }
            if( scoreIt( gs, res ) ) { cout << endl << "Загаданное вами число: " << gs << endl; return; }
            cout << "|    " << gs << "    |  " << setw( 3 ) << res.first << "     |  " << setw( 3 ) << res.second << "    |\n-----------------------------------\n";
            clearPool( gs, res );
        }
    }

    string gimmeANumber()
    {
        if( pool.empty() ) return "";
        return pool[rand() % pool.size()];
    }

    void clearPool( string gs, pair<int, int>& r )
    {
        vector<string>::iterator pi = pool.begin();
        while( pi != pool.end() )
        {
            if( removeIt( gs, ( *pi ), r ) ) pi = pool.erase( pi );
            else  pi++;
        }
    }

    bool removeIt( string gs, string ts, pair<int, int>& res )
    {
        pair<int, int> tp;
        getScore( gs, ts, tp );
        return tp != res;
    }

    void fillPool()
    {
        for( int x = 1000; x < 9999; x++ )
        {
            ostringstream strx;
            strx << x;
            if( check( strx.str() ) ) pool.push_back( strx.str() );
        }
    }

    bool check( string strx )
    {
        for( string::iterator sim = strx.begin(); sim != strx.end(); sim++ )
        {
            if( count( strx.begin(), strx.end(), ( *sim ) ) > 1 ) return false;
        }
        return true;
    }

    bool scoreIt( string gs, pair<int, int>& res )
    {
        getScore( gs, answer, res );
        return res.first == LEN;
    }

    void getScore( string gs, string st, pair<int, int>& pr )
    {
        pr.first = pr.second = 0;
        for( int ui = 0; ui < LEN; ui++ )
        {
            if( gs[ui] == st[ui] ) pr.first++;
            else
            {
                for( int vi = 0; vi < LEN; vi++ )
                    if( gs[ui] == st[vi] ) pr.second++;
            }
        }
    }


    string answer;
    vector<string> pool;
};
//--------------------------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    srand( static_cast<unsigned int>( time( NULL ) ) ); CowsAndBulls_Player cb;
    cb.play(); cout << endl << endl;


}
//--------------------------------------------------------------------------------------------------

