
////////////////////////////////////////////////////////////////////////////
//
// DNS processing
//
////////////////////////////////////////////////////////////////////////////

#ifndef CYBERMON_DNS_H
#define CYBERMON_DNS_H

#include <stdint.h>

#include <set>

#include "context.h"
#include "manager.h"
#include "serial.h"
#include "protocol.h"
#include "dns_protocol.h"

namespace cybermon {

    // A DNS context.
    class dns_context : public context {
      public:
	
	// Constructor.
        dns_context(manager& m) : context(m) {
	}

	// Constructor, describing flow address and parent pointer.
        dns_context(manager& m, const flow_address& a, context_ptr p) : 
	context(m) { 
	    addr = a; parent = p; 
	}

	// Type is "dns".
	virtual std::string get_type() { return "dns"; }

	typedef boost::shared_ptr<dns_context> ptr;

	static context_ptr create(manager& m, const flow_address& f, 
				  context_ptr par) {
	    context_ptr cp = context_ptr(new dns_context(m, f, par));
	    return cp;
	}

	// Given a flow address, returns the child context.
	static ptr get_or_create(context_ptr base, const flow_address& f) {
	    context_ptr cp = context::get_or_create(base, f, 
						    dns_context::create);
	    ptr sp = boost::dynamic_pointer_cast<dns_context>(cp);
	    return sp;
	}

    };

    class dns {

      public:

	// the DNS header length
	static std::size_t header_length();

	// DNS ident function.
	static bool ident(std::uint16_t source_port, std::uint16_t destination_port, pdu_iter s, pdu_iter e);

	// DNS processing function.
	static void process(manager&, context_ptr c, pdu_iter s, pdu_iter e);

    };

};

#endif

