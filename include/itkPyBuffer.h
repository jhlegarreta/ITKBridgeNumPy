/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __itkPyBuffer_h
#define __itkPyBuffer_h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkImportImageFilter.h"
#include "itkDefaultConvertPixelTraits.h"


// The python header defines _POSIX_C_SOURCE without a preceding #undef
#undef _POSIX_C_SOURCE
#include <Python.h>
#include <arrayobject.h>


namespace itk
{

/** \class PyBuffer
 *  \brief Helper class for converting C buffers into python arrays.
 *
 *  This class will receive a C buffer and create the equivalen python
 *  array. This permits to pass image buffers into python arrays from
 *  the Numeric python package.
 *
 */

template <typename TImage>
class PyBuffer
{
public:
  ///! Standard "Self" typedef.
  typedef PyBuffer         Self;

  /// Type of the image from where the buffer will be converted
  typedef TImage                              ImageType;
  typedef typename ImageType::PixelType       PixelType;
  typedef typename ImageType::SizeType        SizeType;
  typedef typename ImageType::IndexType       IndexType;
  typedef typename ImageType::RegionType      RegionType;
  typedef typename ImageType::PointType       PointType;
  typedef typename ImageType::SpacingType     SpacingType;
  typedef typename ImageType::Pointer         ImagePointer;
  typedef typename DefaultConvertPixelTraits<PixelType>::ComponentType ComponentType;

   /** Image dimension. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      ImageType::ImageDimension);


  /// Type of the import image filter
  typedef ImportImageFilter< ComponentType,
                             ImageDimension >   ImporterType;

  typedef typename ImporterType::Pointer   ImporterPointer;
  typedef typename Image<ComponentType, ImageDimension>::Pointer  OutImagePointer;

  /**
   * Get an Array with the content of the image buffer
   */
  static PyObject * GetArrayFromImage( ImageType * image, bool keepAxes = false);

  /**
   * Get an ITK image from a Python array
   */
  static const OutImagePointer GetImageFromArray( PyObject *obj );


protected:
  PyBuffer(const Self&);     // Not implemented.
  void operator=(const Self&); // Not implemented.

};

template <class T> struct PyTypeTraits; // the primary template is empty, by design.
template<> struct PyTypeTraits<double> { enum { value = NPY_DOUBLE }; };
template<> struct PyTypeTraits<float> { enum { value = NPY_FLOAT }; };
template<> struct PyTypeTraits<long>{ enum { value = NPY_LONG }; };
#ifdef NDARRAY_VERSION
template<> struct PyTypeTraits<unsigned long>{ enum { value = NPY_ULONG }; };
#endif
template<> struct PyTypeTraits<int>{ enum { value = NPY_INT }; };
template<> struct PyTypeTraits<short>{ enum { value = NPY_UINT }; };
template<> struct PyTypeTraits<unsigned short>{ enum { value = NPY_SHORT }; };
template<> struct PyTypeTraits<signed char>{ enum { value = NPY_BYTE }; };
template<> struct PyTypeTraits<unsigned char>{ enum { value = NPY_UBYTE }; };

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPyBuffer.hxx"
#endif

#endif // _itkPyBuffer_h
