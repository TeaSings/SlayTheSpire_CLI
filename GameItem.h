#ifndef GameItem_h
#define GameItem_h

template<typename T> class GameItem{
private:
    T _data;
    static int s_alive_count;
public:
    GameItem(T item)
    : _data(item)
    { s_alive_count++; }
    ~GameItem() { s_alive_count--; }

    inline const T& getData() const { return _data; }
    static int getAliveCount()  { return s_alive_count; }
};

template<typename T>
int GameItem<T>::s_alive_count = 0;

#endif