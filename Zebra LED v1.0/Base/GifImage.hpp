// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Gifimage.pas' rev: 21.00

#ifndef GifimageHPP
#define GifimageHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Gifimage
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TGIFVersion { gvUnknown, gv87a, gv89a };
#pragma option pop

typedef StaticArray<char, 3> TGIFVersionRec;

class DELPHICLASS GIFException;
class PASCALIMPLEMENTATION GIFException : public Graphics::EInvalidGraphic
{
	typedef Graphics::EInvalidGraphic inherited;
	
public:
	/* Exception.Create */ inline __fastcall GIFException(const System::UnicodeString Msg) : Graphics::EInvalidGraphic(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall GIFException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : Graphics::EInvalidGraphic(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ inline __fastcall GIFException(int Ident)/* overload */ : Graphics::EInvalidGraphic(Ident) { }
	/* Exception.CreateResFmt */ inline __fastcall GIFException(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : Graphics::EInvalidGraphic(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ inline __fastcall GIFException(const System::UnicodeString Msg, int AHelpContext) : Graphics::EInvalidGraphic(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall GIFException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : Graphics::EInvalidGraphic(Msg, Args, Args_Size, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall GIFException(int Ident, int AHelpContext)/* overload */ : Graphics::EInvalidGraphic(Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall GIFException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : Graphics::EInvalidGraphic(ResStringRec, Args, Args_Size, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~GIFException(void) { }
	
};


#pragma option push -b-
enum TGIFSeverity { gsInfo, gsWarning, gsError };
#pragma option pop

class DELPHICLASS TGIFItem;
class DELPHICLASS TGIFImage;
class PASCALIMPLEMENTATION TGIFItem : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
private:
	TGIFImage* FGIFImage;
	
protected:
	virtual TGIFVersion __fastcall GetVersion(void);
	virtual void __fastcall Warning(TGIFSeverity Severity, System::UnicodeString Message);
	
public:
	__fastcall virtual TGIFItem(TGIFImage* GIFImage);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream) = 0 ;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream) = 0 ;
	virtual void __fastcall SaveToFile(const System::UnicodeString Filename);
	virtual void __fastcall LoadFromFile(const System::UnicodeString Filename);
	__property TGIFVersion Version = {read=GetVersion, nodefault};
	__property TGIFImage* Image = {read=FGIFImage};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGIFItem(void) { }
	
};


class DELPHICLASS TGIFList;
class PASCALIMPLEMENTATION TGIFList : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
public:
	TGIFItem* operator[](int Index) { return Items[Index]; }
	
private:
	Classes::TList* FItems;
	TGIFImage* FImage;
	
protected:
	TGIFItem* __fastcall GetItem(int Index);
	void __fastcall SetItem(int Index, TGIFItem* Item);
	int __fastcall GetCount(void);
	virtual void __fastcall Warning(TGIFSeverity Severity, System::UnicodeString Message);
	
public:
	__fastcall TGIFList(TGIFImage* Image);
	__fastcall virtual ~TGIFList(void);
	int __fastcall Add(TGIFItem* Item);
	void __fastcall Clear(void);
	void __fastcall Delete(int Index);
	void __fastcall Exchange(int Index1, int Index2);
	TGIFItem* __fastcall First(void);
	int __fastcall IndexOf(TGIFItem* Item);
	void __fastcall Insert(int Index, TGIFItem* Item);
	TGIFItem* __fastcall Last(void);
	void __fastcall Move(int CurIndex, int NewIndex);
	int __fastcall Remove(TGIFItem* Item);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream, System::TObject* Parent) = 0 ;
	__property TGIFItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property int Count = {read=GetCount, nodefault};
	__property Classes::TList* List = {read=FItems};
	__property TGIFImage* Image = {read=FImage};
};


#pragma pack(push,1)
struct TGIFColor
{
	
public:
	System::Byte Red;
	System::Byte Green;
	System::Byte Blue;
};
#pragma pack(pop)


typedef StaticArray<TGIFColor, 256> TColorMap;

typedef TColorMap *PColorMap;

struct TUsageCount
{
	
public:
	int Count;
	int Index;
};


typedef StaticArray<TUsageCount, 256> TColormapHistogram;

typedef StaticArray<System::Byte, 256> TColormapReverse;

class DELPHICLASS TGIFColorMap;
class PASCALIMPLEMENTATION TGIFColorMap : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
public:
	Graphics::TColor operator[](int Index) { return Colors[Index]; }
	
private:
	TColorMap *FColorMap;
	int FCount;
	int FCapacity;
	bool FOptimized;
	
protected:
	Graphics::TColor __fastcall GetColor(int Index);
	void __fastcall SetColor(int Index, Graphics::TColor Value);
	int __fastcall GetBitsPerPixel(void);
	bool __fastcall DoOptimize(void);
	void __fastcall SetCapacity(int Size);
	virtual void __fastcall Warning(TGIFSeverity Severity, System::UnicodeString Message) = 0 ;
	virtual void __fastcall BuildHistogram(TUsageCount *Histogram) = 0 ;
	virtual void __fastcall MapImages(System::Byte *Map) = 0 ;
	
public:
	__fastcall TGIFColorMap(void);
	__fastcall virtual ~TGIFColorMap(void);
	__classmethod TGIFColor __fastcall Color2RGB(Graphics::TColor Color);
	__classmethod Graphics::TColor __fastcall RGB2Color(TGIFColor Color);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromStream(Classes::TStream* Stream, int Count);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	int __fastcall IndexOf(Graphics::TColor Color);
	int __fastcall Add(Graphics::TColor Color);
	int __fastcall AddUnique(Graphics::TColor Color);
	void __fastcall Delete(int Index);
	void __fastcall Clear(void);
	virtual bool __fastcall Optimize(void) = 0 ;
	virtual void __fastcall Changed(void) = 0 ;
	void __fastcall ImportPalette(HPALETTE Palette);
	void __fastcall ImportColorTable(void * Pal, int Count);
	void __fastcall ImportDIBColors(HDC Handle);
	void __fastcall ImportColorMap(TGIFColor *Map, int Count);
	HPALETTE __fastcall ExportPalette(void);
	__property Graphics::TColor Colors[int Index] = {read=GetColor, write=SetColor/*, default*/};
	__property PColorMap Data = {read=FColorMap};
	__property int Count = {read=FCount, nodefault};
	__property bool Optimized = {read=FOptimized, write=FOptimized, nodefault};
	__property int BitsPerPixel = {read=GetBitsPerPixel, nodefault};
};


#pragma pack(push,1)
struct TLogicalScreenDescriptor
{
	
public:
	System::Word ScreenWidth;
	System::Word ScreenHeight;
	System::Byte PackedFields;
	System::Byte BackgroundColorIndex;
	System::Byte AspectRatio;
};
#pragma pack(pop)


class DELPHICLASS TGIFHeader;
class PASCALIMPLEMENTATION TGIFHeader : public TGIFItem
{
	typedef TGIFItem inherited;
	
private:
	TLogicalScreenDescriptor FLogicalScreenDescriptor;
	TGIFColorMap* FColorMap;
	void __fastcall Prepare(void);
	
protected:
	virtual TGIFVersion __fastcall GetVersion(void);
	Graphics::TColor __fastcall GetBackgroundColor(void);
	void __fastcall SetBackgroundColor(Graphics::TColor Color);
	void __fastcall SetBackgroundColorIndex(System::Byte Index);
	int __fastcall GetBitsPerPixel(void);
	int __fastcall GetColorResolution(void);
	
public:
	__fastcall virtual TGIFHeader(TGIFImage* GIFImage);
	__fastcall virtual ~TGIFHeader(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall Clear(void);
	__property TGIFVersion Version = {read=GetVersion, nodefault};
	__property System::Word Width = {read=FLogicalScreenDescriptor.ScreenWidth, write=FLogicalScreenDescriptor.ScreenWidth, nodefault};
	__property System::Word Height = {read=FLogicalScreenDescriptor.ScreenHeight, write=FLogicalScreenDescriptor.ScreenHeight, nodefault};
	__property System::Byte BackgroundColorIndex = {read=FLogicalScreenDescriptor.BackgroundColorIndex, write=SetBackgroundColorIndex, nodefault};
	__property Graphics::TColor BackgroundColor = {read=GetBackgroundColor, write=SetBackgroundColor, nodefault};
	__property System::Byte AspectRatio = {read=FLogicalScreenDescriptor.AspectRatio, write=FLogicalScreenDescriptor.AspectRatio, nodefault};
	__property TGIFColorMap* ColorMap = {read=FColorMap};
	__property int BitsPerPixel = {read=GetBitsPerPixel, nodefault};
	__property int ColorResolution = {read=GetColorResolution, nodefault};
};


typedef System::Byte TGIFExtensionType;

typedef TMetaClass* TGIFExtensionClass;

class DELPHICLASS TGIFExtension;
class DELPHICLASS TGIFSubImage;
class PASCALIMPLEMENTATION TGIFExtension : public TGIFItem
{
	typedef TGIFItem inherited;
	
private:
	TGIFSubImage* FSubImage;
	
protected:
	virtual System::Byte __fastcall GetExtensionType(void) = 0 ;
	virtual TGIFVersion __fastcall GetVersion(void);
	System::Byte __fastcall DoReadFromStream(Classes::TStream* Stream);
	__classmethod void __fastcall RegisterExtension(System::Byte elabel, TGIFExtensionClass eClass);
	__classmethod TGIFExtensionClass __fastcall FindExtension(Classes::TStream* Stream);
	__classmethod virtual TGIFExtensionClass __fastcall FindSubExtension(Classes::TStream* Stream);
	
public:
	__fastcall virtual TGIFExtension(TGIFSubImage* ASubImage);
	__fastcall virtual ~TGIFExtension(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	__property System::Byte ExtensionType = {read=GetExtensionType, nodefault};
	__property TGIFSubImage* SubImage = {read=FSubImage};
};


class DELPHICLASS TGIFExtensionList;
class PASCALIMPLEMENTATION TGIFExtensionList : public TGIFList
{
	typedef TGIFList inherited;
	
public:
	TGIFExtension* operator[](int Index) { return Extensions[Index]; }
	
protected:
	TGIFExtension* __fastcall GetExtension(int Index);
	void __fastcall SetExtension(int Index, TGIFExtension* Extension);
	
public:
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream, System::TObject* Parent);
	__property TGIFExtension* Extensions[int Index] = {read=GetExtension, write=SetExtension/*, default*/};
public:
	/* TGIFList.Create */ inline __fastcall TGIFExtensionList(TGIFImage* Image) : TGIFList(Image) { }
	/* TGIFList.Destroy */ inline __fastcall virtual ~TGIFExtensionList(void) { }
	
};


#pragma pack(push,1)
struct TImageDescriptor
{
	
public:
	System::Byte Separator;
	System::Word Left;
	System::Word Top;
	System::Word Width;
	System::Word Height;
	System::Byte PackedFields;
};
#pragma pack(pop)


class DELPHICLASS TGIFGraphicControlExtension;
class PASCALIMPLEMENTATION TGIFSubImage : public TGIFItem
{
	typedef TGIFItem inherited;
	
private:
	Graphics::TBitmap* FBitmap;
	HBITMAP FMask;
	bool FNeedMask;
	HPALETTE FLocalPalette;
	char *FData;
	int FDataSize;
	TGIFColorMap* FColorMap;
	TImageDescriptor FImageDescriptor;
	TGIFExtensionList* FExtensions;
	bool FTransparent;
	TGIFGraphicControlExtension* FGCE;
	void __fastcall Prepare(void);
	void __fastcall Compress(Classes::TStream* Stream);
	void __fastcall Decompress(Classes::TStream* Stream);
	
protected:
	virtual TGIFVersion __fastcall GetVersion(void);
	bool __fastcall GetInterlaced(void);
	void __fastcall SetInterlaced(bool Value);
	int __fastcall GetColorResolution(void);
	int __fastcall GetBitsPerPixel(void);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	Graphics::TBitmap* __fastcall DoGetBitmap(void);
	Graphics::TBitmap* __fastcall DoGetDitherBitmap(void);
	Graphics::TBitmap* __fastcall GetBitmap(void);
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall FreeMask(void);
	bool __fastcall GetEmpty(void);
	HPALETTE __fastcall GetPalette(void);
	void __fastcall SetPalette(HPALETTE Value);
	TGIFColorMap* __fastcall GetActiveColorMap(void);
	Types::TRect __fastcall GetBoundsRect(void);
	void __fastcall SetBoundsRect(const Types::TRect &Value);
	void __fastcall DoSetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	Types::TRect __fastcall GetClientRect(void);
	System::Byte __fastcall GetPixel(int x, int y);
	void __fastcall SetPixel(int x, int y, System::Byte Value);
	void * __fastcall GetScanline(int y);
	void __fastcall NewBitmap(void);
	void __fastcall FreeBitmap(void);
	void __fastcall NewImage(void);
	void __fastcall FreeImage(void);
	void __fastcall NeedImage(void);
	Types::TRect __fastcall ScaleRect(const Types::TRect &DestRect);
	bool __fastcall HasMask(void);
	System::Word __fastcall GetBounds(int Index);
	void __fastcall SetBounds(int Index, System::Word Value);
	bool __fastcall GetHasBitmap(void);
	void __fastcall SetHasBitmap(bool Value);
	
public:
	__fastcall virtual TGIFSubImage(TGIFImage* GIFImage);
	__fastcall virtual ~TGIFSubImage(void);
	void __fastcall Clear(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall Draw(Graphics::TCanvas* ACanvas, const Types::TRect &Rect, bool DoTransparent, bool DoTile);
	void __fastcall StretchDraw(Graphics::TCanvas* ACanvas, const Types::TRect &Rect, bool DoTransparent, bool DoTile);
	void __fastcall Crop(void);
	void __fastcall Merge(TGIFSubImage* Previous);
	__property bool HasBitmap = {read=GetHasBitmap, write=SetHasBitmap, nodefault};
	__property System::Word Left = {read=GetBounds, write=SetBounds, index=1, nodefault};
	__property System::Word Top = {read=GetBounds, write=SetBounds, index=2, nodefault};
	__property System::Word Width = {read=GetBounds, write=SetBounds, index=3, nodefault};
	__property System::Word Height = {read=GetBounds, write=SetBounds, index=4, nodefault};
	__property Types::TRect BoundsRect = {read=GetBoundsRect, write=SetBoundsRect};
	__property Types::TRect ClientRect = {read=GetClientRect};
	__property bool Interlaced = {read=GetInterlaced, write=SetInterlaced, nodefault};
	__property TGIFColorMap* ColorMap = {read=FColorMap};
	__property TGIFColorMap* ActiveColorMap = {read=GetActiveColorMap};
	__property char * Data = {read=FData};
	__property int DataSize = {read=FDataSize, nodefault};
	__property TGIFExtensionList* Extensions = {read=FExtensions};
	__property TGIFVersion Version = {read=GetVersion, nodefault};
	__property int ColorResolution = {read=GetColorResolution, nodefault};
	__property int BitsPerPixel = {read=GetBitsPerPixel, nodefault};
	__property Graphics::TBitmap* Bitmap = {read=GetBitmap, write=SetBitmap};
	__property HBITMAP Mask = {read=FMask, nodefault};
	__property HPALETTE Palette = {read=GetPalette, write=SetPalette, nodefault};
	__property bool Empty = {read=GetEmpty, nodefault};
	__property bool Transparent = {read=FTransparent, nodefault};
	__property TGIFGraphicControlExtension* GraphicControlExtension = {read=FGCE};
	__property System::Byte Pixels[int x][int y] = {read=GetPixel, write=SetPixel};
	__property void * Scanline[int y] = {read=GetScanline};
};


class DELPHICLASS TGIFTrailer;
class PASCALIMPLEMENTATION TGIFTrailer : public TGIFItem
{
	typedef TGIFItem inherited;
	
__published:
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
public:
	/* TGIFItem.Create */ inline __fastcall virtual TGIFTrailer(TGIFImage* GIFImage) : TGIFItem(GIFImage) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGIFTrailer(void) { }
	
};


#pragma pack(push,1)
struct TGIFGCERec
{
	
public:
	System::Byte BlockSize;
	System::Byte PackedFields;
	System::Word DelayTime;
	System::Byte TransparentColorIndex;
	System::Byte Terminator;
};
#pragma pack(pop)


#pragma option push -b-
enum TDisposalMethod { dmNone, dmNoDisposal, dmBackground, dmPrevious };
#pragma option pop

class PASCALIMPLEMENTATION TGIFGraphicControlExtension : public TGIFExtension
{
	typedef TGIFExtension inherited;
	
private:
	TGIFGCERec FGCExtension;
	
protected:
	virtual System::Byte __fastcall GetExtensionType(void);
	bool __fastcall GetTransparent(void);
	void __fastcall SetTransparent(bool Value);
	Graphics::TColor __fastcall GetTransparentColor(void);
	void __fastcall SetTransparentColor(Graphics::TColor Color);
	System::Byte __fastcall GetTransparentColorIndex(void);
	void __fastcall SetTransparentColorIndex(System::Byte Value);
	System::Word __fastcall GetDelay(void);
	void __fastcall SetDelay(System::Word Value);
	bool __fastcall GetUserInput(void);
	void __fastcall SetUserInput(bool Value);
	TDisposalMethod __fastcall GetDisposal(void);
	void __fastcall SetDisposal(TDisposalMethod Value);
	
public:
	__fastcall virtual TGIFGraphicControlExtension(TGIFSubImage* ASubImage);
	__fastcall virtual ~TGIFGraphicControlExtension(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	__property System::Word Delay = {read=GetDelay, write=SetDelay, nodefault};
	__property bool Transparent = {read=GetTransparent, write=SetTransparent, nodefault};
	__property System::Byte TransparentColorIndex = {read=GetTransparentColorIndex, write=SetTransparentColorIndex, nodefault};
	__property Graphics::TColor TransparentColor = {read=GetTransparentColor, write=SetTransparentColor, nodefault};
	__property bool UserInput = {read=GetUserInput, write=SetUserInput, nodefault};
	__property TDisposalMethod Disposal = {read=GetDisposal, write=SetDisposal, nodefault};
};


#pragma pack(push,1)
struct TGIFPlainTextExtensionRec
{
	
public:
	System::Byte BlockSize;
	System::Word Left;
	System::Word Top;
	System::Word Width;
	System::Word Height;
	System::Byte CellWidth;
	System::Byte CellHeight;
	System::Byte TextFGColorIndex;
	System::Byte TextBGColorIndex;
};
#pragma pack(pop)


class DELPHICLASS TGIFTextExtension;
class PASCALIMPLEMENTATION TGIFTextExtension : public TGIFExtension
{
	typedef TGIFExtension inherited;
	
private:
	Classes::TStrings* FText;
	TGIFPlainTextExtensionRec FPlainTextExtension;
	
protected:
	virtual System::Byte __fastcall GetExtensionType(void);
	Graphics::TColor __fastcall GetForegroundColor(void);
	void __fastcall SetForegroundColor(Graphics::TColor Color);
	Graphics::TColor __fastcall GetBackgroundColor(void);
	void __fastcall SetBackgroundColor(Graphics::TColor Color);
	System::Word __fastcall GetBounds(int Index);
	void __fastcall SetBounds(int Index, System::Word Value);
	System::Byte __fastcall GetCharWidthHeight(int Index);
	void __fastcall SetCharWidthHeight(int Index, System::Byte Value);
	System::Byte __fastcall GetColorIndex(int Index);
	void __fastcall SetColorIndex(int Index, System::Byte Value);
	
public:
	__fastcall virtual TGIFTextExtension(TGIFSubImage* ASubImage);
	__fastcall virtual ~TGIFTextExtension(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	__property System::Word Left = {read=GetBounds, write=SetBounds, index=1, nodefault};
	__property System::Word Top = {read=GetBounds, write=SetBounds, index=2, nodefault};
	__property System::Word GridWidth = {read=GetBounds, write=SetBounds, index=3, nodefault};
	__property System::Word GridHeight = {read=GetBounds, write=SetBounds, index=4, nodefault};
	__property System::Byte CharWidth = {read=GetCharWidthHeight, write=SetCharWidthHeight, index=1, nodefault};
	__property System::Byte CharHeight = {read=GetCharWidthHeight, write=SetCharWidthHeight, index=2, nodefault};
	__property System::Byte ForegroundColorIndex = {read=GetColorIndex, write=SetColorIndex, index=1, nodefault};
	__property Graphics::TColor ForegroundColor = {read=GetForegroundColor, nodefault};
	__property System::Byte BackgroundColorIndex = {read=GetColorIndex, write=SetColorIndex, index=2, nodefault};
	__property Graphics::TColor BackgroundColor = {read=GetBackgroundColor, nodefault};
	__property Classes::TStrings* Text = {read=FText, write=FText};
};


class DELPHICLASS TGIFCommentExtension;
class PASCALIMPLEMENTATION TGIFCommentExtension : public TGIFExtension
{
	typedef TGIFExtension inherited;
	
private:
	Classes::TStrings* FText;
	
protected:
	virtual System::Byte __fastcall GetExtensionType(void);
	
public:
	__fastcall virtual TGIFCommentExtension(TGIFSubImage* ASubImage);
	__fastcall virtual ~TGIFCommentExtension(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	__property Classes::TStrings* Text = {read=FText};
};


typedef StaticArray<char, 8> TGIFIdentifierCode;

typedef StaticArray<char, 3> TGIFAuthenticationCode;

#pragma pack(push,1)
struct TGIFApplicationRec
{
	
public:
	TGIFIdentifierCode Identifier;
	TGIFAuthenticationCode Authentication;
};
#pragma pack(pop)


typedef TMetaClass* TGIFAppExtensionClass;

class DELPHICLASS TGIFApplicationExtension;
class PASCALIMPLEMENTATION TGIFApplicationExtension : public TGIFExtension
{
	typedef TGIFExtension inherited;
	
private:
	TGIFApplicationRec FIdent;
	System::AnsiString __fastcall GetAuthentication(void);
	System::AnsiString __fastcall GetIdentifier(void);
	
protected:
	virtual System::Byte __fastcall GetExtensionType(void);
	void __fastcall SetAuthentication(const System::AnsiString Value);
	void __fastcall SetIdentifier(const System::AnsiString Value);
	virtual void __fastcall SaveData(Classes::TStream* Stream) = 0 ;
	virtual void __fastcall LoadData(Classes::TStream* Stream) = 0 ;
	
public:
	__fastcall virtual TGIFApplicationExtension(TGIFSubImage* ASubImage);
	__fastcall virtual ~TGIFApplicationExtension(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	__classmethod void __fastcall RegisterExtension(const TGIFApplicationRec &eIdent, TGIFAppExtensionClass eClass);
	__classmethod virtual TGIFExtensionClass __fastcall FindSubExtension(Classes::TStream* Stream);
	__property System::AnsiString Identifier = {read=GetIdentifier, write=SetIdentifier};
	__property System::AnsiString Authentication = {read=GetAuthentication, write=SetAuthentication};
};


class DELPHICLASS TGIFBlock;
class PASCALIMPLEMENTATION TGIFBlock : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Byte FSize;
	void *FData;
	
public:
	__fastcall TGIFBlock(int ASize);
	__fastcall virtual ~TGIFBlock(void);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	__property System::Byte Size = {read=FSize, nodefault};
	__property void * Data = {read=FData};
};


class DELPHICLASS TGIFUnknownAppExtension;
class PASCALIMPLEMENTATION TGIFUnknownAppExtension : public TGIFApplicationExtension
{
	typedef TGIFApplicationExtension inherited;
	
private:
	Classes::TList* FBlocks;
	
protected:
	virtual void __fastcall SaveData(Classes::TStream* Stream);
	virtual void __fastcall LoadData(Classes::TStream* Stream);
	
public:
	__fastcall virtual TGIFUnknownAppExtension(TGIFSubImage* ASubImage);
	__fastcall virtual ~TGIFUnknownAppExtension(void);
	__property Classes::TList* Blocks = {read=FBlocks};
};


class DELPHICLASS TGIFAppExtNSLoop;
class PASCALIMPLEMENTATION TGIFAppExtNSLoop : public TGIFApplicationExtension
{
	typedef TGIFApplicationExtension inherited;
	
private:
	System::Word FLoops;
	unsigned FBufferSize;
	
protected:
	virtual void __fastcall SaveData(Classes::TStream* Stream);
	virtual void __fastcall LoadData(Classes::TStream* Stream);
	
public:
	__fastcall virtual TGIFAppExtNSLoop(TGIFSubImage* ASubImage);
	__property System::Word Loops = {read=FLoops, write=FLoops, nodefault};
	__property unsigned BufferSize = {read=FBufferSize, write=FBufferSize, nodefault};
public:
	/* TGIFApplicationExtension.Destroy */ inline __fastcall virtual ~TGIFAppExtNSLoop(void) { }
	
};


class DELPHICLASS TGIFImageList;
class PASCALIMPLEMENTATION TGIFImageList : public TGIFList
{
	typedef TGIFList inherited;
	
public:
	TGIFSubImage* operator[](int Index) { return SubImages[Index]; }
	
protected:
	TGIFSubImage* __fastcall GetImage(int Index);
	void __fastcall SetImage(int Index, TGIFSubImage* SubImage);
	
public:
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream, System::TObject* Parent);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	__property TGIFSubImage* SubImages[int Index] = {read=GetImage, write=SetImage/*, default*/};
public:
	/* TGIFList.Create */ inline __fastcall TGIFImageList(TGIFImage* Image) : TGIFList(Image) { }
	/* TGIFList.Destroy */ inline __fastcall virtual ~TGIFImageList(void) { }
	
};


#pragma option push -b-
enum TGIFCompression { gcLZW, gcRLE };
#pragma option pop

#pragma option push -b-
enum TColorReduction { rmNone, rmWindows20, rmWindows256, rmWindowsGray, rmMonochrome, rmGrayScale, rmNetscape, rmQuantize, rmQuantizeWindows, rmPalette };
#pragma option pop

#pragma option push -b-
enum TDitherMode { dmNearest, dmFloydSteinberg, dmStucki, dmSierra, dmJaJuNI, dmSteveArche, dmBurkes };
#pragma option pop

#pragma option push -b-
enum TGIFOptimizeOption { ooCrop, ooMerge, ooCleanup, ooColorMap, ooReduceColors };
#pragma option pop

typedef Set<TGIFOptimizeOption, ooCrop, ooReduceColors>  TGIFOptimizeOptions;

#pragma option push -b-
enum TGIFDrawOption { goAsync, goTransparent, goAnimate, goLoop, goLoopContinously, goValidateCanvas, goDirectDraw, goClearOnLoop, goTile, goDither, goAutoDither };
#pragma option pop

typedef Set<TGIFDrawOption, goAsync, goAutoDither>  TGIFDrawOptions;

class DELPHICLASS TGIFPainter;
typedef TGIFPainter* *PGIFPainter;

class PASCALIMPLEMENTATION TGIFPainter : public Classes::TThread
{
	typedef Classes::TThread inherited;
	
private:
	TGIFImage* FImage;
	Graphics::TCanvas* FCanvas;
	Types::TRect FRect;
	TGIFDrawOptions FDrawOptions;
	int FAnimationSpeed;
	int FActiveImage;
	TDisposalMethod Disposal;
	TDisposalMethod OldDisposal;
	Graphics::TBitmap* BackupBuffer;
	Graphics::TBitmap* FrameBuffer;
	Graphics::TBitmap* Background;
	HDC ValidateDC;
	bool DoRestart;
	bool FStarted;
	TGIFPainter* *PainterRef;
	unsigned FEventHandle;
	Sysutils::Exception* ExceptObject;
	void *ExceptAddress;
	Classes::TNotifyEvent FEvent;
	Classes::TNotifyEvent FOnStartPaint;
	Classes::TNotifyEvent FOnPaint;
	Classes::TNotifyEvent FOnAfterPaint;
	Classes::TNotifyEvent FOnLoop;
	Classes::TNotifyEvent FOnEndPaint;
	void __fastcall DoOnTerminate(System::TObject* Sender);
	void __fastcall DoSynchronize(Classes::TThreadMethod Method);
	void __fastcall DoPaintFrame(void);
	void __fastcall DoPaint(void);
	void __fastcall DoEvent(void);
	void __fastcall SetActiveImage(const int Value);
	
protected:
	virtual void __fastcall Execute(void);
	void __fastcall SetAnimationSpeed(int Value);
	
public:
	__fastcall TGIFPainter(TGIFImage* AImage, Graphics::TCanvas* ACanvas, const Types::TRect &ARect, TGIFDrawOptions Options);
	__fastcall TGIFPainter(PGIFPainter Painter, TGIFImage* AImage, Graphics::TCanvas* ACanvas, const Types::TRect &ARect, TGIFDrawOptions Options);
	__fastcall virtual ~TGIFPainter(void);
	HIDESBASE void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall Restart(void);
	__property TGIFImage* Image = {read=FImage};
	__property Graphics::TCanvas* Canvas = {read=FCanvas};
	__property Types::TRect Rect = {read=FRect, write=FRect};
	__property TGIFDrawOptions DrawOptions = {read=FDrawOptions, write=FDrawOptions, nodefault};
	__property int AnimationSpeed = {read=FAnimationSpeed, write=SetAnimationSpeed, nodefault};
	__property bool Started = {read=FStarted, nodefault};
	__property int ActiveImage = {read=FActiveImage, write=SetActiveImage, nodefault};
	__property Classes::TNotifyEvent OnStartPaint = {read=FOnStartPaint, write=FOnStartPaint};
	__property Classes::TNotifyEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Classes::TNotifyEvent OnAfterPaint = {read=FOnAfterPaint, write=FOnAfterPaint};
	__property Classes::TNotifyEvent OnLoop = {read=FOnLoop, write=FOnLoop};
	__property Classes::TNotifyEvent OnEndPaint = {read=FOnEndPaint, write=FOnEndPaint};
	__property unsigned EventHandle = {read=FEventHandle, nodefault};
};


typedef void __fastcall (__closure *TGIFWarning)(System::TObject* Sender, TGIFSeverity Severity, System::UnicodeString Message);

class PASCALIMPLEMENTATION TGIFImage : public Graphics::TGraphic
{
	typedef Graphics::TGraphic inherited;
	
private:
	bool IsDrawing;
	bool IsInsideGetPalette;
	TGIFImageList* FImages;
	TGIFHeader* FHeader;
	HPALETTE FGlobalPalette;
	Classes::TThreadList* FPainters;
	TGIFDrawOptions FDrawOptions;
	TColorReduction FColorReduction;
	int FReductionBits;
	TDitherMode FDitherMode;
	TGIFCompression FCompression;
	TGIFWarning FOnWarning;
	Graphics::TBitmap* FBitmap;
	TGIFPainter* FDrawPainter;
	Classes::TThreadPriority FThreadPriority;
	int FAnimationSpeed;
	int FForceFrame;
	Graphics::TColor FDrawBackgroundColor;
	Classes::TNotifyEvent FOnStartPaint;
	Classes::TNotifyEvent FOnPaint;
	Classes::TNotifyEvent FOnAfterPaint;
	Classes::TNotifyEvent FOnLoop;
	Classes::TNotifyEvent FOnEndPaint;
	bool __fastcall GetAnimate(void);
	void __fastcall SetAnimate(const bool Value);
	void __fastcall SetForceFrame(const int Value);
	
protected:
	virtual int __fastcall GetHeight(void);
	virtual void __fastcall SetHeight(int Value);
	virtual int __fastcall GetWidth(void);
	virtual void __fastcall SetWidth(int Value);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	TGIFPainter* __fastcall InternalPaint(PGIFPainter Painter, Graphics::TCanvas* ACanvas, const Types::TRect &Rect, TGIFDrawOptions Options);
	virtual void __fastcall Draw(Graphics::TCanvas* ACanvas, const Types::TRect &Rect);
	virtual bool __fastcall Equals(Graphics::TGraphic* Graphic)/* overload */;
	virtual HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall SetPalette(HPALETTE Value);
	virtual bool __fastcall GetEmpty(void);
	virtual void __fastcall WriteData(Classes::TStream* Stream);
	bool __fastcall GetIsTransparent(void);
	TGIFVersion __fastcall GetVersion(void);
	int __fastcall GetColorResolution(void);
	int __fastcall GetBitsPerPixel(void);
	System::Byte __fastcall GetBackgroundColorIndex(void);
	void __fastcall SetBackgroundColorIndex(const System::Byte Value);
	Graphics::TColor __fastcall GetBackgroundColor(void);
	void __fastcall SetBackgroundColor(const Graphics::TColor Value);
	System::Byte __fastcall GetAspectRatio(void);
	void __fastcall SetAspectRatio(const System::Byte Value);
	void __fastcall SetDrawOptions(TGIFDrawOptions Value);
	void __fastcall SetAnimationSpeed(int Value);
	void __fastcall SetReductionBits(int Value);
	void __fastcall NewImage(void);
	Graphics::TBitmap* __fastcall GetBitmap(void);
	Graphics::TBitmap* __fastcall NewBitmap(void);
	void __fastcall FreeBitmap(void);
	TGIFColorMap* __fastcall GetColorMap(void);
	bool __fastcall GetDoDither(void);
	__property TGIFPainter* DrawPainter = {read=FDrawPainter};
	__property bool DoDither = {read=GetDoDither, nodefault};
	void __fastcall FixHeaderWidthHeight(void);
	
public:
	__fastcall virtual TGIFImage(void);
	__fastcall virtual ~TGIFImage(void);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall LoadFromResourceName(unsigned Instance, const System::UnicodeString ResName);
	int __fastcall Add(Classes::TPersistent* Source);
	void __fastcall Pack(void);
	void __fastcall OptimizeColorMap(void);
	void __fastcall Optimize(TGIFOptimizeOptions Options, TColorReduction ColorReduction, TDitherMode DitherMode, int ReductionBits);
	void __fastcall Clear(void);
	void __fastcall StopDraw(void);
	TGIFPainter* __fastcall Paint(Graphics::TCanvas* ACanvas, const Types::TRect &Rect, TGIFDrawOptions Options);
	void __fastcall PaintStart(void);
	void __fastcall PaintPause(void);
	void __fastcall PaintStop(void);
	void __fastcall PaintResume(void);
	void __fastcall PaintRestart(void);
	virtual void __fastcall Warning(System::TObject* Sender, TGIFSeverity Severity, System::UnicodeString Message);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall LoadFromClipboardFormat(System::Word AFormat, unsigned AData, HPALETTE APalette);
	virtual void __fastcall SaveToClipboardFormat(System::Word &AFormat, unsigned &AData, HPALETTE &APalette);
	__property TGIFColorMap* GlobalColorMap = {read=GetColorMap};
	__property TGIFVersion Version = {read=GetVersion, nodefault};
	__property TGIFImageList* Images = {read=FImages};
	__property int ColorResolution = {read=GetColorResolution, nodefault};
	__property int BitsPerPixel = {read=GetBitsPerPixel, nodefault};
	__property System::Byte BackgroundColorIndex = {read=GetBackgroundColorIndex, write=SetBackgroundColorIndex, nodefault};
	__property Graphics::TColor BackgroundColor = {read=GetBackgroundColor, write=SetBackgroundColor, nodefault};
	__property System::Byte AspectRatio = {read=GetAspectRatio, write=SetAspectRatio, nodefault};
	__property TGIFHeader* Header = {read=FHeader};
	__property bool IsTransparent = {read=GetIsTransparent, nodefault};
	__property TGIFDrawOptions DrawOptions = {read=FDrawOptions, write=SetDrawOptions, nodefault};
	__property Graphics::TColor DrawBackgroundColor = {read=FDrawBackgroundColor, write=FDrawBackgroundColor, nodefault};
	__property TColorReduction ColorReduction = {read=FColorReduction, write=FColorReduction, nodefault};
	__property int ReductionBits = {read=FReductionBits, write=SetReductionBits, nodefault};
	__property TDitherMode DitherMode = {read=FDitherMode, write=FDitherMode, nodefault};
	__property TGIFCompression Compression = {read=FCompression, write=FCompression, nodefault};
	__property int AnimationSpeed = {read=FAnimationSpeed, write=SetAnimationSpeed, nodefault};
	__property bool Animate = {read=GetAnimate, write=SetAnimate, nodefault};
	__property int ForceFrame = {read=FForceFrame, write=SetForceFrame, nodefault};
	__property Classes::TThreadList* Painters = {read=FPainters};
	__property Classes::TThreadPriority ThreadPriority = {read=FThreadPriority, write=FThreadPriority, nodefault};
	__property Graphics::TBitmap* Bitmap = {read=GetBitmap};
	__property TGIFWarning OnWarning = {read=FOnWarning, write=FOnWarning};
	__property Classes::TNotifyEvent OnStartPaint = {read=FOnStartPaint, write=FOnStartPaint};
	__property Classes::TNotifyEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Classes::TNotifyEvent OnAfterPaint = {read=FOnAfterPaint, write=FOnAfterPaint};
	__property Classes::TNotifyEvent OnLoop = {read=FOnLoop, write=FOnLoop};
	__property Classes::TNotifyEvent OnEndPaint = {read=FOnEndPaint, write=FOnEndPaint};
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  Equals(System::TObject* Obj){ return Graphics::TGraphic::Equals(Obj); }
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word GIFVersion = 0x202;
static const ShortInt GIFVersionMajor = 0x2;
static const ShortInt GIFVersionMinor = 0x2;
static const ShortInt GIFVersionRelease = 0x5;
static const Word GIFMaxColors = 0x100;
static const int BitmapAllocationThreshold = 0x7a120;
extern PACKAGE int GIFDelayExp;
extern PACKAGE int GIFDefaultDelay;
extern PACKAGE int GIFMinimumDelay;
extern PACKAGE int GIFMaximumDelay;
extern PACKAGE StaticArray<StaticArray<char, 3>, 2> GIFVersions;
extern PACKAGE System::Word CF_GIF;
extern PACKAGE TGIFDrawOptions GIFImageDefaultDrawOptions;
extern PACKAGE TColorReduction GIFImageDefaultColorReduction;
extern PACKAGE int GIFImageDefaultColorReductionBits;
extern PACKAGE TDitherMode GIFImageDefaultDitherMode;
extern PACKAGE TGIFCompression GIFImageDefaultCompression;
extern PACKAGE Classes::TThreadPriority GIFImageDefaultThreadPriority;
extern PACKAGE int GIFImageDefaultAnimationSpeed;
extern PACKAGE bool DoAutoDither;
extern PACKAGE bool PaletteDevice;
extern PACKAGE bool GIFImageRenderOnLoad;
extern PACKAGE bool GIFImageOptimizeOnStream;
extern PACKAGE System::ResourceString _sOutOfData;
#define Gifimage_sOutOfData System::LoadResourceString(&Gifimage::_sOutOfData)
extern PACKAGE System::ResourceString _sTooManyColors;
#define Gifimage_sTooManyColors System::LoadResourceString(&Gifimage::_sTooManyColors)
extern PACKAGE System::ResourceString _sBadColorIndex;
#define Gifimage_sBadColorIndex System::LoadResourceString(&Gifimage::_sBadColorIndex)
extern PACKAGE System::ResourceString _sBadVersion;
#define Gifimage_sBadVersion System::LoadResourceString(&Gifimage::_sBadVersion)
extern PACKAGE System::ResourceString _sBadSignature;
#define Gifimage_sBadSignature System::LoadResourceString(&Gifimage::_sBadSignature)
extern PACKAGE System::ResourceString _sScreenBadColorSize;
#define Gifimage_sScreenBadColorSize System::LoadResourceString(&Gifimage::_sScreenBadColorSize)
extern PACKAGE System::ResourceString _sImageBadColorSize;
#define Gifimage_sImageBadColorSize System::LoadResourceString(&Gifimage::_sImageBadColorSize)
extern PACKAGE System::ResourceString _sUnknownExtension;
#define Gifimage_sUnknownExtension System::LoadResourceString(&Gifimage::_sUnknownExtension)
extern PACKAGE System::ResourceString _sBadExtensionLabel;
#define Gifimage_sBadExtensionLabel System::LoadResourceString(&Gifimage::_sBadExtensionLabel)
extern PACKAGE System::ResourceString _sOutOfMemDIB;
#define Gifimage_sOutOfMemDIB System::LoadResourceString(&Gifimage::_sOutOfMemDIB)
extern PACKAGE System::ResourceString _sDIBCreate;
#define Gifimage_sDIBCreate System::LoadResourceString(&Gifimage::_sDIBCreate)
extern PACKAGE System::ResourceString _sDecodeTooFewBits;
#define Gifimage_sDecodeTooFewBits System::LoadResourceString(&Gifimage::_sDecodeTooFewBits)
extern PACKAGE System::ResourceString _sDecodeCircular;
#define Gifimage_sDecodeCircular System::LoadResourceString(&Gifimage::_sDecodeCircular)
extern PACKAGE System::ResourceString _sBadTrailer;
#define Gifimage_sBadTrailer System::LoadResourceString(&Gifimage::_sBadTrailer)
extern PACKAGE System::ResourceString _sBadExtensionInstance;
#define Gifimage_sBadExtensionInstance System::LoadResourceString(&Gifimage::_sBadExtensionInstance)
extern PACKAGE System::ResourceString _sBadBlockSize;
#define Gifimage_sBadBlockSize System::LoadResourceString(&Gifimage::_sBadBlockSize)
extern PACKAGE System::ResourceString _sBadBlock;
#define Gifimage_sBadBlock System::LoadResourceString(&Gifimage::_sBadBlock)
extern PACKAGE System::ResourceString _sUnsupportedClass;
#define Gifimage_sUnsupportedClass System::LoadResourceString(&Gifimage::_sUnsupportedClass)
extern PACKAGE System::ResourceString _sInvalidData;
#define Gifimage_sInvalidData System::LoadResourceString(&Gifimage::_sInvalidData)
extern PACKAGE System::ResourceString _sBadHeight;
#define Gifimage_sBadHeight System::LoadResourceString(&Gifimage::_sBadHeight)
extern PACKAGE System::ResourceString _sBadWidth;
#define Gifimage_sBadWidth System::LoadResourceString(&Gifimage::_sBadWidth)
extern PACKAGE System::ResourceString _sFailedPaste;
#define Gifimage_sFailedPaste System::LoadResourceString(&Gifimage::_sFailedPaste)
extern PACKAGE System::ResourceString _sScreenSizeExceeded;
#define Gifimage_sScreenSizeExceeded System::LoadResourceString(&Gifimage::_sScreenSizeExceeded)
extern PACKAGE System::ResourceString _sNoColorTable;
#define Gifimage_sNoColorTable System::LoadResourceString(&Gifimage::_sNoColorTable)
extern PACKAGE System::ResourceString _sBadPixelCoordinates;
#define Gifimage_sBadPixelCoordinates System::LoadResourceString(&Gifimage::_sBadPixelCoordinates)
extern PACKAGE System::ResourceString _sUnsupportedBitmap;
#define Gifimage_sUnsupportedBitmap System::LoadResourceString(&Gifimage::_sUnsupportedBitmap)
extern PACKAGE System::ResourceString _sInvalidPixelFormat;
#define Gifimage_sInvalidPixelFormat System::LoadResourceString(&Gifimage::_sInvalidPixelFormat)
extern PACKAGE System::ResourceString _sBadDimension;
#define Gifimage_sBadDimension System::LoadResourceString(&Gifimage::_sBadDimension)
extern PACKAGE System::ResourceString _sNoDIB;
#define Gifimage_sNoDIB System::LoadResourceString(&Gifimage::_sNoDIB)
extern PACKAGE System::ResourceString _sInvalidStream;
#define Gifimage_sInvalidStream System::LoadResourceString(&Gifimage::_sInvalidStream)
extern PACKAGE System::ResourceString _sInvalidColor;
#define Gifimage_sInvalidColor System::LoadResourceString(&Gifimage::_sInvalidColor)
extern PACKAGE System::ResourceString _sInvalidBitSize;
#define Gifimage_sInvalidBitSize System::LoadResourceString(&Gifimage::_sInvalidBitSize)
extern PACKAGE System::ResourceString _sEmptyColorMap;
#define Gifimage_sEmptyColorMap System::LoadResourceString(&Gifimage::_sEmptyColorMap)
extern PACKAGE System::ResourceString _sEmptyImage;
#define Gifimage_sEmptyImage System::LoadResourceString(&Gifimage::_sEmptyImage)
extern PACKAGE System::ResourceString _sInvalidBitmapList;
#define Gifimage_sInvalidBitmapList System::LoadResourceString(&Gifimage::_sInvalidBitmapList)
extern PACKAGE System::ResourceString _sInvalidReduction;
#define Gifimage_sInvalidReduction System::LoadResourceString(&Gifimage::_sInvalidReduction)
extern PACKAGE System::ResourceString _sGIFImageFile;
#define Gifimage_sGIFImageFile System::LoadResourceString(&Gifimage::_sGIFImageFile)
extern PACKAGE System::ResourceString _sProgressLoading;
#define Gifimage_sProgressLoading System::LoadResourceString(&Gifimage::_sProgressLoading)
extern PACKAGE System::ResourceString _sProgressSaving;
#define Gifimage_sProgressSaving System::LoadResourceString(&Gifimage::_sProgressSaving)
extern PACKAGE System::ResourceString _sProgressConverting;
#define Gifimage_sProgressConverting System::LoadResourceString(&Gifimage::_sProgressConverting)
extern PACKAGE System::ResourceString _sProgressRendering;
#define Gifimage_sProgressRendering System::LoadResourceString(&Gifimage::_sProgressRendering)
extern PACKAGE System::ResourceString _sProgressCopying;
#define Gifimage_sProgressCopying System::LoadResourceString(&Gifimage::_sProgressCopying)
extern PACKAGE System::ResourceString _sProgressOptimizing;
#define Gifimage_sProgressOptimizing System::LoadResourceString(&Gifimage::_sProgressOptimizing)
extern PACKAGE void __fastcall Register(void);
extern PACKAGE HPALETTE __fastcall WebPalette(void);
extern PACKAGE void __fastcall InternalGetDIBSizes(HBITMAP Bitmap, int &InfoHeaderSize, int &ImageSize, Graphics::TPixelFormat PixelFormat);
extern PACKAGE bool __fastcall InternalGetDIB(HBITMAP Bitmap, HPALETTE Palette, void *BitmapInfo, void *Bits, Graphics::TPixelFormat PixelFormat);
extern PACKAGE HPALETTE __fastcall CreateOptimizedPaletteFromManyBitmaps(Classes::TList* Bitmaps, int Colors, int ColorBits, bool Windows);
extern PACKAGE Graphics::TBitmap* __fastcall ReduceColors(Graphics::TBitmap* Bitmap, TColorReduction ColorReduction, TDitherMode DitherMode, int ReductionBits, HPALETTE CustomPalette);

}	/* namespace Gifimage */
using namespace Gifimage;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GifimageHPP
