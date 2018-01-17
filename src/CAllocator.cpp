#include "CAllocator.h"
#include <stdlib.h>     /* malloc, free */
#include <assert.h>
#include <algorithm>    // max

CAllocator::CAllocator()
    : Allocator(0) {

}

void CAllocator::Init() {

}

CAllocator::~CAllocator(){
    
}

void* CAllocator::Allocate(const std::size_t size, const std::size_t alignment) {
	static char msg[64] ;

	void* p = malloc(size);
	if( !p ) {
		sprintf_s(msg,sizeof(msg),"Cannot allocate %Iu bytes", size) ;
		throw std::exception( msg ) ;
	}
	m_peak = std::max(m_peak, size);
	return p ;
}

void CAllocator::Free(void* ptr) {
	free(ptr);
}


