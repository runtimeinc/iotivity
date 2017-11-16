//
//  Iotivity.h
//  mobilegateway
//
//  Created by Brian Giori on 11/13/17.
//  Copyright © 2017 Brian Giori. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IotivityClient;
@class OcResource;
@class OcRepresentation;
@class OcRepresentationValue;

typedef void (^DiscoverCallback)(NSArray<OcResource*>* resources);
typedef void (^GetCallback)(OcRepresentation* representation);
typedef void (^PutCallback)(OcRepresentation* representation);
typedef void (^ObserveCallback)(OcRepresentation* representation);

#define IOTIVITY_UUID "ADE3D529-C784-4F63-A987-EB69F70EE816"
