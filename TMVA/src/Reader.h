// @(#)root/tmva $Id: Reader.h,v 1.1.2.1 2012/01/04 18:54:06 caebergs Exp $ 
// Author: Andreas Hoecker, Joerg Stelzer, Helge Voss, Kai Voss 

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : Reader                                                                *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Reader class to be used in the user application to interpret the trained  *
 *      MVAs in an analysis context                                               *
 *                                                                                *
 * Authors (alphabetical order):                                                  *
 *      Andreas Hoecker <Andreas.Hocker@cern.ch> - CERN, Switzerland              *
 *      Peter Speckmayer <peter.speckmayer@cern.ch> - CERN, Switzerland           *
 *      Joerg Stelzer <Joerg.Stelzer@cern.ch>    - CERN, Switzerland              *
 *      Helge Voss      <Helge.Voss@cern.ch>     - MPI-K Heidelberg, Germany      *
 *      Kai Voss        <Kai.Voss@cern.ch>       - U. of Victoria, Canada         *
 *                                                                                *
 * Copyright (c) 2005:                                                            *
 *      CERN, Switzerland                                                         * 
 *      U. of Victoria, Canada                                                    * 
 *      MPI-K Heidelberg, Germany                                                 * 
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://ttmva.sourceforge.net/LICENSE)                                         *
 **********************************************************************************/

#ifndef ROOT_TMVA_Reader
#define ROOT_TMVA_Reader

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Reader                                                               //
//                                                                      //
// Reader class to be used in the user application to interpret the     //
// trained MVAs in an analysis context                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TMVA_Configurable
#include "TMVA/Configurable.h"
#endif
#ifndef ROOT_TMVA_Types
#include "TMVA/Types.h"
#endif
#ifndef ROOT_TMVA_DataSetInfo
#include "TMVA/DataSetInfo.h"
#endif
#ifndef ROOT_TMVA_DataInputHandler
#include "TMVA/DataInputHandler.h"
#endif
#ifndef ROOT_TMVA_DataSetManager
#include "TMVA/DataSetManager.h"
#endif

#include <vector>
#include <map>
#include <stdexcept>

namespace TMVA {

   class IMethod;
   class MethodBase;
   class DataSetInfo;
   class MethodCuts;

   class Reader : public Configurable {

   public:
      
      // without prior specification of variables
      Reader( const TString& theOption="", Bool_t verbose = 0 );

      // STL types
      Reader( std::vector<std::string>& varNames, const TString& theOption = "", Bool_t verbose = 0 );
      Reader( const std::string& varNames, const TString& theOption, Bool_t verbose = 0 );  // format: "var1:var2:..."

      // Root types
      Reader( std::vector<TString>& varNames, const TString& theOption = "", Bool_t verbose = 0 );
      Reader( const TString& varNames, const TString& theOption, Bool_t verbose = 0 );  // format: "var1:var2:..."

      virtual ~Reader( void );
  
      // book MVA method via weight file
      IMethod* BookMVA( const TString& methodTag, const TString& weightfile );
      IMethod* FindMVA( const TString& methodTag );
      // special function for Cuts to avoid dynamic_casts in ROOT macros, 
      // which are not properly handled by CINT
      MethodCuts* FindCutsMVA( const TString& methodTag ); 
      

      // returns the MVA response for given event
      Double_t EvaluateMVA( const std::vector<Float_t> &, const TString& methodTag, Double_t aux = 0 );    
      Double_t EvaluateMVA( const std::vector<Double_t>&, const TString& methodTag, Double_t aux = 0 );    
      Double_t EvaluateMVA( MethodBase* method,           Double_t aux = 0 );    
      Double_t EvaluateMVA( const TString& methodTag,     Double_t aux = 0 );    

      // returns error on MVA response for given event
      // NOTE: must be called AFTER "EvaluateMVA(...)" call !
      Double_t GetMVAError() const { return fMvaEventError; }

      const std::vector< Float_t >& EvaluateRegression( const TString& methodTag, Double_t aux = 0 );
      const std::vector< Float_t >& EvaluateRegression( MethodBase* method, Double_t aux = 0 );
      Float_t  EvaluateRegression( UInt_t tgtNumber, const TString& methodTag, Double_t aux = 0 );

      // probability and rarity accessors (see Users Guide for definition of Rarity)
      Double_t GetProba ( const TString& methodTag, Double_t ap_sig=0.5, Double_t mvaVal=-9999999 ); 
      Double_t GetRarity( const TString& methodTag, Double_t mvaVal=-9999999 );

      // accessors 
      virtual const char* GetName() const { return "Reader"; }
      Bool_t   Verbose( void ) const  { return fVerbose; }
      void     SetVerbose( Bool_t v ) { fVerbose = v; }

      const DataSetInfo& DataInfo() const { return fDataSetInfo; }
      DataSetInfo&       DataInfo()       { return fDataSetInfo; }
      
      void     AddVariable( const TString& expression, Float_t* );
      void     AddVariable( const TString& expression, Int_t* );

      void     AddSpectator( const TString& expression, Float_t* );
      void     AddSpectator( const TString& expression, Int_t* );


  
   private:

      TString GetMethodTypeFromFile( const TString& filename );

      // this booking method is internal
      IMethod* BookMVA( Types::EMVA method,  const TString& weightfile );

      DataSetInfo fDataSetInfo; // the data set

      DataInputHandler fDataInputHandler;

      // Init Reader class
      void Init( void );

      // Decode Constructor string (or TString) and fill variable name std::vector
      void DecodeVarNames( const std::string& varNames );
      void DecodeVarNames( const TString& varNames );

      void DeclareOptions();

      Bool_t    fVerbose;    // verbosity
      Bool_t    fSilent;     // silent mode
      Bool_t    fColor;      // color mode

      Double_t  fMvaEventError; // per-event error returned by MVA (unless: -1)

      std::map<TString, IMethod*> fMethodMap; // map of methods

      mutable MsgLogger* fLogger;   // message logger
      MsgLogger& Log() const { return *fLogger; }    

      ClassDef(Reader,0) // Interpret the trained MVAs in an analysis context
   };

}

#endif
