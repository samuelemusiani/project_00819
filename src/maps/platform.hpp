class Platform
{
    private:
        int x_pos;
        int y_pos;
        int length;
    public:
        Platform();
        Platform(int x,int y,int len);

        void set_xPosition(int x);
        void set_yPosition(int y);
        void set_length(int len);

        int get_xPosition();
        int get_yPosition();
        int get_length();
};