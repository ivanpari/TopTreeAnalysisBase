// @(#)root/tmva $Id: TNeuronInput.h,v 1.1.2.1 2012/01/04 18:54:10 caebergs Exp $
// Author: Matt Jachowski 

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : TMVA::TNeuronInput                                                    *
 *                                                                                *
 * Description:                                                                   *
 *      Interface for TNeuron input calculation classes                           *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Matt Jachowski  <jachowski@stanford.edu> - Stanford University, USA       *
 *                                                                                *
 * Copyright (c) 2005:                                                            *
 *      CERN, Switzerland                                                         *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 **********************************************************************************/
 

#ifndef ROOT_TMVA_TNeuronInput
#define ROOT_TMVA_TNeuronInput

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TNeuronInput                                                         //
//                                                                      //
// Interface for TNeuron input calculation classes                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TObject
#include "TObject.h"
#endif
#ifndef ROOT_TString
#include "TString.h"
#endif

namespace TMVA {

   class TNeuron;
  
   class TNeuronInput {
    
   public:

      TNeuronInput() {}
      virtual ~TNeuronInput() {}

      // calculate input value for neuron
      virtual Double_t GetInput( const TNeuron* neuron ) const = 0;

      // name of class
      virtual TString GetName() = 0;

      ClassDef(TNeuronInput,0) // Interface for TNeuron input calculation classes
   };

} // namespace TMVA

#endif
