class IGameControl
{
public:
	void SetPosition(POINT *pPosition)=0;
	POINT* GetPosition()=0;

	void SetSize(SIZE *size)=0;
	SIZE* GetSize()=0;

	void SetText(TCHAR *lpszText)=0;
	TCHAR *GetText()=0;


};