#include "shellprv.h"
#include <regstr.h>
#include <shellp.h>
#include "ole2dup.h"
#include "ids.h"
#include "defview.h"
#include <perhist.h>
#include "defvphst.h"

// Docfind Persistent history implemention.
STDMETHODIMP CDefViewPersistHistory::QueryInterface(REFIID riid, void **ppvObj)
{
    static const QITAB qit[] = {
        QITABENT(CDefViewPersistHistory, IPersistHistory),             //IID_IPersistHistory
        QITABENTMULTI(CDefViewPersistHistory, IPersist, IPersistHistory), //IID_IPersist
        QITABENT(CDefViewPersistHistory, IObjectWithSite),              //IID_IOBjectWithSite
        QITABENT(CDefViewPersistHistory, IOleObject),                  // IID_IOleObject
        { 0 },
    };

    return QISearch(this, qit, riid, ppvObj);
}

STDMETHODIMP_(ULONG) CDefViewPersistHistory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CDefViewPersistHistory::Release()
{
    ASSERT( 0 != m_cRef );
    ULONG cRef = InterlockedDecrement(&m_cRef);
    if ( 0 == cRef )
    {
        delete this;
    }
    return cRef;
}


CDefViewPersistHistory::CDefViewPersistHistory() :
        m_cRef(1)       
{
}

CDefViewPersistHistory::~CDefViewPersistHistory()
{   
}


STDAPI CDefViewPersistHistory_CreateInstance(IUnknown *punkOuter, REFIID riid, void **ppv)
{
    HRESULT   hr;

    CDefViewPersistHistory *pdfph = new CDefViewPersistHistory();
    if (!pdfph)
    {
        *ppv = NULL;
        return E_OUTOFMEMORY;
    }

    hr = pdfph->QueryInterface(riid, ppv);
    pdfph->Release();
    return hr;    
}


// Functions to support persisting the document into the history stream...
STDMETHODIMP CDefViewPersistHistory::GetClassID(CLSID *pClassID)
{
    *pClassID = CLSID_DefViewPersistHistory;
    return S_OK;
}


STDMETHODIMP CDefViewPersistHistory::LoadHistory(IStream *pstm, IBindCtx *pbc)
{
    IShellView *psv;
    if (_punkSite && SUCCEEDED(_punkSite->QueryInterface(IID_PPV_ARG(IShellView, &psv))))
    {           
        UINT cItems = 0;
        LPITEMIDLIST pidl = NULL;    // don't free previous one
        UINT uFlags = SVSI_FOCUSED | SVSI_SELECT | SVSI_DESELECTOTHERS | SVSI_ENSUREVISIBLE;

        // read how many pidls we stored
        pstm->Read(&cItems, sizeof(cItems), NULL);

        // now read the pidls
        for (UINT i=0; i < cItems ; i++)
        {
            if (FAILED(ILLoadFromStream(pstm, &pidl)) || (pidl == NULL))
                break;
            if (SUCCEEDED(psv->SelectItem(pidl, uFlags)))
                uFlags = SVSI_SELECT;
        }
        if (pidl)
            ILFree(pidl);       // Free the last one read in

        //
        // If we are in webview mode, we need to load the Trident persist history too
        // 
        IPersistHistory * piph;
        if (SUCCEEDED(IUnknown_QueryService(_punkSite, SID_WebViewObject, IID_PPV_ARG(IPersistHistory, &piph))))
        {
            piph->LoadHistory(pstm, pbc);
            piph->Release();
        }                 
        psv->Release();
    }

    return S_OK;
}


STDMETHODIMP CDefViewPersistHistory::SaveHistory(IStream *pstm)
{
    IShellFolderView *psfv;
    if (_punkSite && SUCCEEDED(_punkSite->QueryInterface(IID_PPV_ARG(IShellFolderView, &psfv))))
    {   
        LPCITEMIDLIST *apidl;
        UINT cItems;
      
        // FEATURE: Currently this assumes the first item is focused. There are cases
        // where we may have unslected the focused item and we are not saving this out here.
        //
        // Need to add GetFocusedObject() to IShellFolderView interface to query this
        //
        //
        if (SUCCEEDED(psfv->GetSelectedObjects(&apidl, &cItems)) && cItems)
        {

            // write out how many pidls we have
            pstm->Write(&cItems, sizeof(cItems), NULL);

            // now write the pidls
            for (UINT i = 0; i < cItems; i++)
            {
                if (apidl[i])
                    ILSaveToStream(pstm, apidl[i]);
            }
            LocalFree((HLOCAL)apidl);
        }
        else
        {   
            cItems = 0;
            pstm->Write(&cItems, sizeof(cItems), NULL);
        }
        
        //
        // If we are in webview mode, we need to save the Trident persist history too
        // 
        IPersistHistory * piph;
        if (SUCCEEDED(IUnknown_QueryService(_punkSite, SID_WebViewObject, IID_PPV_ARG(IPersistHistory, &piph))))
        {
            piph->SaveHistory(pstm);
            piph->Release();
        }               
                
        psfv->Release();
    }
    return S_OK;
}


STDMETHODIMP CDefViewPersistHistory::SetPositionCookie(DWORD dwPositioncookie)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::SetPositionCookie - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::GetPositionCookie(DWORD *pdwPositioncookie)
{
    *pdwPositioncookie = 0;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::GetPositionCookie - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::SetClientSite(IOleClientSite *pClientSite)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::SetClientSite - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::GetClientSite(IOleClientSite **ppClientSite)
{
    *ppClientSite = NULL;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::GetClientSite - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::SetHostNames - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::Close(DWORD dwSaveOption)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::Close - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::SetMoniker(DWORD dwWhichMoniker, IMoniker *pmk)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::SetMoniker - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
    *ppmk = NULL;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::GetMoniker - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::InitFromData(IDataObject *pDataObject,BOOL fCreation,DWORD dwReserved)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::InitFromData - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::GetClipboardData(DWORD dwReserved,IDataObject **ppDataObject)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::GetClipboardData - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::DoVerb(LONG iVerb,LPMSG lpmsg,IOleClientSite *pActiveSite,LONG lindex,HWND hwndParent,LPCRECT lprcPosRect)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::DoVerb - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::EnumVerbs(IEnumOLEVERB **ppEnumOleVerb)
{
    *ppEnumOleVerb = NULL;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::EnumVerbs - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::Update(void)
{
    // Always up to date.
    return S_OK;
}

STDMETHODIMP CDefViewPersistHistory::IsUpToDate(void)
{
    return S_OK;    // say we are alwayes up to date.
}

STDMETHODIMP CDefViewPersistHistory::GetUserClassID(CLSID *pClsid)
{
    return GetClassID(pClsid);
}

STDMETHODIMP CDefViewPersistHistory::GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType)
{
    *pszUserType = NULL;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::GetUserType - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::SetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::SetExtent - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::GetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::GetExtent - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::Advise(IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
    *pdwConnection = 0;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::Advise - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::Unadvise(DWORD dwConnection)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::Unadvise - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::EnumAdvise(IEnumSTATDATA **ppenumAdvise)
{
    *ppenumAdvise = NULL;
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::EnumAdvises - not implemented"));
    return E_NOTIMPL;
}

STDMETHODIMP CDefViewPersistHistory::GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus)
{
    *pdwStatus = 0;
    if (dwAspect == DVASPECT_CONTENT)
        *pdwStatus = OLEMISC_SETCLIENTSITEFIRST;
    return S_OK;
}

STDMETHODIMP CDefViewPersistHistory::SetColorScheme(LOGPALETTE *pLogpal)
{
    DebugMsg(DM_ERROR, TEXT("CDefViewPersistHistory::SetColorScheme - not implemented"));
    return E_NOTIMPL;
}


