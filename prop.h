EXTERN_C const SHCOLUMNID SCID_Author;
EXTERN_C const SHCOLUMNID SCID_Title;
EXTERN_C const SHCOLUMNID SCID_Subject;
EXTERN_C const SHCOLUMNID SCID_Category;
EXTERN_C const SHCOLUMNID SCID_Copyright;
EXTERN_C const SHCOLUMNID SCID_CompanyName;
EXTERN_C const SHCOLUMNID SCID_PageCount;
EXTERN_C const SHCOLUMNID SCID_Comment;
EXTERN_C const SHCOLUMNID SCID_DocCreated;
EXTERN_C const SHCOLUMNID SCID_TYPE;
EXTERN_C const SHCOLUMNID SCID_WRITETIME;
EXTERN_C const SHCOLUMNID SCID_CREATETIME;
EXTERN_C const SHCOLUMNID SCID_ACCESSTIME;
EXTERN_C const SHCOLUMNID SCID_OWNER;
EXTERN_C const SHCOLUMNID SCID_NAME;
EXTERN_C const SHCOLUMNID SCID_DELETEDFROM;
EXTERN_C const SHCOLUMNID SCID_DATEDELETED;
EXTERN_C const SHCOLUMNID SCID_SIZE;
EXTERN_C const SHCOLUMNID SCID_SYNCCOPYIN;
EXTERN_C const SHCOLUMNID SCID_STATUS;
EXTERN_C const SHCOLUMNID SCID_DIRECTORY;
EXTERN_C const SHCOLUMNID SCID_RANK;
EXTERN_C const SHCOLUMNID SCID_FREESPACE;
EXTERN_C const SHCOLUMNID SCID_CAPACITY;
EXTERN_C const SHCOLUMNID SCID_FILESYSTEM;
EXTERN_C const SHCOLUMNID SCID_CSC_STATUS;
EXTERN_C const SHCOLUMNID SCID_LINKTARGET;
EXTERN_C const SHCOLUMNID SCID_LASTVISITED;
EXTERN_C const SHCOLUMNID SCID_LASTMODIFIED;
EXTERN_C const SHCOLUMNID SCID_VISITCOUNT;
EXTERN_C const SHCOLUMNID SCID_ATTRIBUTES;
EXTERN_C const SHCOLUMNID SCID_ATTRIBUTES_DESCRIPTION;
EXTERN_C const SHCOLUMNID SCID_LOCATION;
EXTERN_C const SHCOLUMNID SCID_FINDDATA;
EXTERN_C const SHCOLUMNID SCID_NETRESOURCE;
EXTERN_C const SHCOLUMNID SCID_DESCRIPTIONID;
EXTERN_C const SHCOLUMNID SCID_WHICHFOLDER;
EXTERN_C const SHCOLUMNID SCID_NETWORKLOCATION;
EXTERN_C const SHCOLUMNID SCID_COMPUTERNAME;
EXTERN_C const SHCOLUMNID SCID_DetailsProperties;
EXTERN_C const SHCOLUMNID SCID_FolderIntroText;
EXTERN_C const SHCOLUMNID SCID_CONTROLPANELCATEGORY;
EXTERN_C const SHCOLUMNID SCID_MUSIC_Artist;
EXTERN_C const SHCOLUMNID SCID_MUSIC_Album;
EXTERN_C const SHCOLUMNID SCID_MUSIC_Year;
EXTERN_C const SHCOLUMNID SCID_MUSIC_Track;
EXTERN_C const SHCOLUMNID SCID_MUSIC_Genre;
EXTERN_C const SHCOLUMNID SCID_AUDIO_Duration;
EXTERN_C const SHCOLUMNID SCID_AUDIO_Bitrate;
EXTERN_C const SHCOLUMNID SCID_ImageCX;
EXTERN_C const SHCOLUMNID SCID_ImageCY;
EXTERN_C const SHCOLUMNID SCID_ImageDimensions;
EXTERN_C const SHCOLUMNID SCID_CameraModel;
EXTERN_C const SHCOLUMNID SCID_WhenTaken;
EXTERN_C const SHCOLUMNID SCID_Flash;
EXTERN_C const SHCOLUMNID SCID_ColorSpace;
EXTERN_C const SHCOLUMNID SCID_DRM_Protected;

// Printer Folder column identifier defs...
EXTERN_C const SHCOLUMNID SCID_PRN_QUEUESIZE;
EXTERN_C const SHCOLUMNID SCID_PRN_STATUS;
EXTERN_C const SHCOLUMNID SCID_PRN_LOCATION;
EXTERN_C const SHCOLUMNID SCID_PRN_MODEL;

//  Win32 PE (exe, dll) Version Information column identifier defs...
EXTERN_C const SHCOLUMNID SCID_FileDescription;
EXTERN_C const SHCOLUMNID SCID_FileVersion;
EXTERN_C const SHCOLUMNID SCID_InternalName;
EXTERN_C const SHCOLUMNID SCID_OriginalFileName;
EXTERN_C const SHCOLUMNID SCID_ProductName;
EXTERN_C const SHCOLUMNID SCID_ProductVersion;

typedef struct {
    const SHCOLUMNID *pscid;
    VARTYPE vt;             // Note that the type of a given FMTID/PID pair is a known, fixed value
    DWORD fmt;              // listview format (LVCFMT_LEFT, usually)
    UINT cChars;            // count of chars (default col width)
    DWORD csFlags;          // SHCOLSTATE flags
    UINT idTitle;           // string id for title
    UINT idDescription;     // add these, make defview display them too!
} COLUMN_INFO;

#define DEFINE_COL_ENTRY(scid, vt, fmt, cChars, shcs, ids) \
    { &scid, vt, fmt, cChars, shcs, ids, 0 }

#define DEFINE_COL_STR_ENTRY(scid, cChars, ids) \
    { &scid, VT_LPWSTR, LVCFMT_LEFT, cChars, SHCOLSTATE_TYPE_STR | SHCOLSTATE_ONBYDEFAULT, ids, 0 }

#define DEFINE_COL_STR_MENU_ENTRY(scid, cChars, ids) \
    { &scid, VT_LPWSTR, LVCFMT_LEFT, cChars, SHCOLSTATE_TYPE_STR, ids, 0 }

#define DEFINE_COL_STR_DLG_ENTRY(scid, cChars, ids) \
    { &scid, VT_LPWSTR, LVCFMT_LEFT, cChars, SHCOLSTATE_TYPE_STR | SHCOLSTATE_SECONDARYUI, ids, 0 }

#define DEFINE_COL_STR_HIDDEN_ENTRY(scid) \
    { &scid, VT_LPWSTR, LVCFMT_LEFT, 20, SHCOLSTATE_TYPE_STR | SHCOLSTATE_HIDDEN, 0, 0 }

#define DEFINE_COL_DATE_ENTRY(scid, ids) \
    { &scid, VT_DATE, LVCFMT_LEFT, 20, SHCOLSTATE_TYPE_DATE | SHCOLSTATE_ONBYDEFAULT, ids, 0 }

#define DEFINE_COL_DATE_HIDDEN_ENTRY(scid) \
    { &scid, VT_DATE, LVCFMT_LEFT, 20, SHCOLSTATE_TYPE_DATE | SHCOLSTATE_HIDDEN, 0, 0 }

#define DEFINE_COL_INT_ENTRY(scid, cChars, ids) \
    { &scid, VT_I4, LVCFMT_LEFT, cChars, SHCOLSTATE_TYPE_INT | SHCOLSTATE_ONBYDEFAULT, ids, 0 }

#define DEFINE_COL_INT_DLG_ENTRY(scid, cChars, ids) \
    { &scid, VT_I4, LVCFMT_LEFT, cChars, SHCOLSTATE_TYPE_INT | SHCOLSTATE_SECONDARYUI, ids, 0 }

#define DEFINE_COL_INT_HIDDEN_ENTRY(scid) \
    { &scid, VT_I4, LVCFMT_LEFT, 5, SHCOLSTATE_TYPE_STR | SHCOLSTATE_HIDDEN, 0, 0 }

#define DEFINE_COL_SIZE_ENTRY(scid, ids) \
    DEFINE_COL_ENTRY(scid, VT_UI8, LVCFMT_RIGHT, 16, SHCOLSTATE_TYPE_INT | SHCOLSTATE_ONBYDEFAULT, ids)


STDAPI GetDetailsOfInfo(const COLUMN_INFO* pcol_data, UINT nCols, UINT iColumn, SHELLDETAILS *pdi);
STDAPI_(int) FindSCID(const COLUMN_INFO* pcol_data, UINT nCols, const SHCOLUMNID* pscid);
STDAPI MapColumnToSCIDImpl(const COLUMN_INFO* pcol_data, UINT nCols, UINT iColumn, SHCOLUMNID* pscid);
STDAPI_(BOOL) ParseSCIDString(LPCTSTR pszString, SHCOLUMNID *pscid, UINT *pidRes);
STDAPI SCIDCannonicalName(SHCOLUMNID *pscid, LPTSTR pszName, int cch);
HRESULT PropVariantToVariant(const PROPVARIANT *pPropVar, VARIANT *pVar);

#define CompareSCIDFMTIDPID(fmtid, pid, scid)   ((pid == (scid).pid) && IsEqualIID(fmtid, (scid).fmtid))
#define DEFINE_SCID(name, fmtid, pid) const SHCOLUMNID name = { fmtid, pid }

//
// Constants used while converting a SCID to a string
//
#define SCID_PIDSTR_MAX     10   // will take care of any long integer value  
#define SCIDSTR_MAX         (GUIDSTR_MAX + 1 + SCID_PIDSTR_MAX)

STDAPI_(int) StringFromSCID(const SHCOLUMNID *pscid, LPTSTR lpsz, UINT cch);

STDAPI SHFormatForDisplay(REFFMTID fmtid, PROPID pid, const PROPVARIANT *pPropVar, 
                          PROPERTYUI_FORMAT_FLAGS flags, LPWSTR pwszText, DWORD cchText);
