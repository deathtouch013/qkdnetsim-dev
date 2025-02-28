/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 LIPTEL.ieee.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Miralem Mehic <miralem.mehic@ieee.org>
 */

#ifndef QKD_HELPER_H
#define QKD_HELPER_H

#include <string>

#include "ns3/object-factory.h"
#include "ns3/qkd-graph-manager.h" 
#include "ns3/net-device-container.h"
#include "ns3/node-container.h" 
#include "ns3/trace-helper.h"
#include "ns3/ipv4-interface-address.h"
#include "ns3/core-module.h"  
#include "ns3/network-module.h"
#include "ns3/internet-module.h" 
#include "ns3/qkd-net-device.h"
#include "ns3/qkd-crypto.h"

#include "ns3/qkd-random-generator.h"

namespace ns3 {
 
class NetDevice;
class Node;

/**
 * \ingroup qkd
 * \class QKDHelper
 * \brief Build a set of QKDNetDevice objects
 *
 * Normally we eschew multiple inheritance, however, the classes 
 * PcapUserHelperForDevice and AsciiTraceUserHelperForDevice are
 * "mixins".
 */
class QKDHelper : public PcapHelperForDevice,
                  public AsciiTraceHelperForDevice
{
public:

    /**
    * Create a QKDHelper to make life easier when creating point to
    * point networks.
    */
    QKDHelper ();
    virtual ~QKDHelper () {}

    /**
    * Each point to point net device must have a queue to pass packets through.
    * This method allows one to set the type of the queue that is automatically
    * created when the device is created and attached to a node.
    *
    * \param type the type of queue
    * \param n1 the name of the attribute to set on the queue
    * \param v1 the value of the attribute to set on the queue
    * \param n2 the name of the attribute to set on the queue
    * \param v2 the value of the attribute to set on the queue
    * \param n3 the name of the attribute to set on the queue
    * \param v3 the value of the attribute to set on the queue
    * \param n4 the name of the attribute to set on the queue
    * \param v4 the value of the attribute to set on the queue
    *
    * Set the type of queue to create and associated to each
    * QKDNetDevice created through QKDHelper::Install.
    */
    void SetQueue (std::string type,
                 std::string n1 = "", const AttributeValue &v1 = EmptyAttributeValue (),
                 std::string n2 = "", const AttributeValue &v2 = EmptyAttributeValue (),
                 std::string n3 = "", const AttributeValue &v3 = EmptyAttributeValue (),
                 std::string n4 = "", const AttributeValue &v4 = EmptyAttributeValue ());

    /**
    * Set an attribute value to be propagated to each NetDevice created by the
    * helper.
    *
    * \param name the name of the attribute to set
    * \param value the value of the attribute to set
    *
    * Set these attributes on each ns3::QKDNetDevice created
    * by QKDHelper::Install
    */
    void SetDeviceAttribute (std::string name, const AttributeValue &value);

    /**
    * Set an attribute value to be propagated to each Channel created by the
    * helper.
    *
    * \param name the name of the attribute to set
    * \param value the value of the attribute to set
    *
    * Set these attribute on each ns3::QKDChannel created
    * by QKDHelper::Install
    */
    void SetChannelAttribute (std::string name, const AttributeValue &value);

    /**
    * \param c a set of nodes
    * \return a NetDeviceContainer for nodes
    *
    * This method creates a ns3::QKDChannel with the
    * attributes configured by QKDHelper::SetChannelAttribute,
    * then, for each node in the input container, we create a 
    * ns3::QKDNetDevice with the requested attributes, 
    * a queue for this ns3::NetDevice, and associate the resulting 
    * ns3::NetDevice with the ns3::Node and ns3::QKDChannel.
    */
    //NetDeviceContainer Install (NodeContainer c);

    /**
    * \param a first node
    * \param b second node
    * \return a NetDeviceContainer for nodes
    *
    * Saves you from having to construct a temporary NodeContainer. 
    * Also, if MPI is enabled, for distributed simulations, 
    * appropriate remote QKD channels are created.
    */
    //NetDeviceContainer Install (Ptr<Node> a, Ptr<Node> b);

    /**
    * \param a first node
    * \param bName name of second node
    * \return a NetDeviceContainer for nodes
    *
    * Saves you from having to construct a temporary NodeContainer.
    */
    //NetDeviceContainer Install (Ptr<Node> a, std::string bName);

    //SINGLE TCP-IP STACK
    NetDeviceContainer InstallQKD (
        Ptr<NetDevice>          IPa,
        Ptr<NetDevice>          IPb, 
        uint32_t                Mmin,
        uint32_t                Mthr,
        uint32_t                Mmax,
        uint32_t                Mcurrent
    );

    //SINGLE TCP-IP STACK
    NetDeviceContainer InstallQKD (Ptr<NetDevice> a, Ptr<NetDevice> b);

    /**
    * \param a first node
    * \param b second node
    * \return a NetDeviceContainer for nodes
    *
    * Saves you from having to construct a temporary NodeContainer. 
    * Also, if MPI is enabled, for distributed simulations, 
    * appropriate remote QKD channels are created.
    */
    NetDeviceContainer InstallOverlayQKD (
        Ptr<NetDevice>          IPa,
        Ptr<NetDevice>          IPb,
        Ipv4InterfaceAddress    da,
        Ipv4InterfaceAddress    db, 
        uint32_t                Mmin,
        uint32_t                Mthr,
        uint32_t                Mmax,
        uint32_t                Mcurrent,
        const std::string       typeId
    );

    NetDeviceContainer InstallOverlayQKD (
        Ptr<NetDevice>          IPa,
        Ptr<NetDevice>          IPb,
        Ipv4InterfaceAddress    da,
        Ipv4InterfaceAddress    db, 
        uint32_t                Mmin,
        uint32_t                Mthr,
        uint32_t                Mmax,
        uint32_t                Mcurrent
    );

    NetDeviceContainer InstallOverlayQKD (Ptr<NetDevice> a, Ptr<NetDevice> b);
    
	void AddGraph(Ptr<Node> node, Ptr<NetDevice> device);

	void AddGraph(Ptr<Node> node, Ptr<NetDevice> device, std::string graphName);
    
    void AddGraph(Ptr<Node> node, Ptr<NetDevice> device, std::string graphName, std::string graphType);

    void PrintGraphs();

    /**
    * \param aName Name of first node
    * \param b second node
    * \return a NetDeviceContainer for nodes
    *
    * Saves you from having to construct a temporary NodeContainer.
    */
    NetDeviceContainer Install (std::string aName, Ptr<Node> b);

    void InstallQKDManager (NodeContainer& n);  

    /**
    * \param aNode Name of first node
    * \param bNode Name of second node
    * \return a NetDeviceContainer for nodes
    *
    * Saves you from having to construct a temporary NodeContainer.
    */
    NetDeviceContainer Install (std::string aNode, std::string bNode);

    /**
    * \brief create an object from its TypeId and aggregates it to the node
    * \param node the node
    * \param typeId the object TypeId
    */
    static void CreateAndAggregateObjectFromTypeId (Ptr<Node> node, const std::string typeId);

    /**
    * \param routing a new routing helper
    *
    * Set the routing helper to use during Install. The routing
    * helper is really an object factory which is used to create 
    * an object of type ns3::Ipv4RoutingProtocol per node. This routing
    * object is then associated to a single ns3::Ipv4 object through its 
    * ns3::Ipv4::SetRoutingProtocol.
    */
    void SetRoutingHelper (const Ipv4RoutingHelper &routing);


    /**
    * Activa la generacion de material de clave con QRNG, 
    * pero tiene que hacerse antes de instalar el QKDManager
    */
    void SetQRNG();

    void SetUseRealStorages(bool useRealStorages);
    void SetEncryptionEnabled(bool EncryptionEnabled);

private:

    /**
    * \brief TCP objects factory
    */
    ObjectFactory m_tcpFactory;

    /**
    * \brief IPv4 routing helper.
    */
    const Ipv4RoutingHelper *m_routing;
 
    uint32_t m_portOverlayNumber; 

    uint32_t m_channelID;

    bool     m_useRealStorages;

    Ptr<QKDCrypto> m_QCrypto;

    uint32_t m_counter;

    uint32_t m_supportQKDL4;

    /**
    * \brief Enable pcap output the indicated net device.
    *
    * NetDevice-specific implementation mechanism for hooking the trace and
    * writing to the trace file.
    *
    * \param prefix Filename prefix to use for pcap files.
    * \param nd Net device for which you want to enable tracing.
    * \param promiscuous If true capture all possible packets available at the device.
    * \param explicitFilename Treat the prefix as an explicit filename if true
    */
    virtual void EnablePcapInternal (std::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename);

    /**
    * \brief Enable ascii trace output on the indicated net device.
    *
    * NetDevice-specific implementation mechanism for hooking the trace and
    * writing to the trace file.
    *
    * \param stream The output stream object to use when logging ascii traces.
    * \param prefix Filename prefix to use for ascii trace files.
    * \param nd Net device for which you want to enable tracing.
    * \param explicitFilename Treat the prefix as an explicit filename if true
    */
     
    virtual void EnableAsciiInternal (
    Ptr<OutputStreamWrapper> stream,
    std::string prefix,
    Ptr<NetDevice> nd,
    bool explicitFilename);

    ObjectFactory m_channelFactory;       //!< Channel Factory 
    ObjectFactory m_deviceFactory;        //!< Device Factory
    bool    m_activeQRNG;     
    QKDRandomGenerator m_randomGenerator;            
}; 
} // namespace ns3

#endif /* QKD_HELPER_H */
