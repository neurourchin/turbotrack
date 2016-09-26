#pragma once
#ifndef INCLUDED__BITFLOW__B_F_G_T_L__UTILITIES__HPP
#define INCLUDED__BITFLOW__B_F_G_T_L__UTILITIES__HPP

#include "BFGTLUtilApi.h"

#include "BFException.hpp"

#include <string>
#include <vector>

/**
 * \namespace BFGTLUtilities
 *
 * \brief Class library for Gen<i>Cam camera device access via BFGTL.
 */

/**
 * \class BFGTLUtilities::Device
 *
 * \brief Interface to access and modify features on a Gen<i>Cam device.
 *
 * The BFGTLUtilities::Device class provides an independent interface to Gen<i>Cam
 * devices, as exposed by BitFlow frame grabbers through the BFGTL Gen<i>Cam producer.
 * This may be used simultaneously with the \ref BufferAcquisition classes, or
 * completely independently. \ref BufferAcquisition::BufferInterface implements its
 * own CXP register methods.
 */

/**
 * \class BFGTLUtilities::BaseNode
 *
 * \brief Base class for \ref BFGTLUtilities::Device node access and modification.
 */

/**
 * \class BFGTLUtilities::ValueNode;
 *
 * \brief \ref BFGTLUtilities::Device node class to access or modify nodes with any kind of value.
 */

/**
 * \class BFGTLUtilities::IntegerNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to access or modify integer value nodes.
 */

/**
 * \class BFGTLUtilities::BooleanNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to access or modify boolean value nodes.
 */

/**
 * \class BFGTLUtilities::CommandNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to execute command nodes.
 */

/**
 * \class BFGTLUtilities::FloatNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to access or modify floating-point value nodes.
 */

/**
 * \class BFGTLUtilities::StringNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to access or modify string value nodes.
 */

/**
 * \class BFGTLUtilities::RegisterNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to access or modify register value nodes.
 */

/**
 * \class BFGTLUtilities::CategoryNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to read category nodes and their features.
 */

/**
 * \class BFGTLUtilities::EnumerationNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to access or modify enumeration value nodes, and read their features.
 */

/**
 * \class BFGTLUtilities::EnumEntryNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to examine enumeration-entry value nodes.
 */

/**
 * \class BFGTLUtilities::PortNode;
 *
 * \brief  \ref BFGTLUtilities::Device node class to examine port nodes.
 */

// Externally defined classes.
namespace BufferAcquisition
{
    class BufferInterface;
}

// The BFGTLUtilities namespace.
namespace BFGTLUtilities
{
    // Static method to determine if the base library can be loaded.
    BFDLL BFBOOL BFCAPI LibIsGood (void);

    // Forward declation(s).
    struct BaseNode;

    // The BFGTL Camera Device.
    class BFDLL Device
    {
    public:
        // Default constructor.
        Device (BFVOID);

        // Destructor.
        ~Device (BFVOID);

        // Returns the number of BitFlow boards installed on this system.
        static BFU32 boardCount (BFVOID);
        
        // Open the Device corresponding to specified BufferInterface. The Device must be closed prior
        // to closing the BufferInterface. Closes the current Device first, if necessary.
        BFVOID open (BufferAcquisition::BufferInterface const& bufin);
        
        // Open the BFGTL Camera Device corresponding to the given board handle. The Device must be
        // closed prior to closing the board handle.  Closes the current Device first, if necessary.
        BFVOID open (Bd hBoard);

        // Open a BFGTL Camera Device for the given board number.  Closes the current Device first,
        // if necessary.
        BFVOID open (const BFU32 brdNum);

        // Open a BFGTL Camera Device for the given Board switch and Connector. Closes the current
        // Device first, if necessary.
        BFVOID openSWConnector (const BFU32 Switch, const BFU32 Connector);

        // Close the BFGTL Camera Device.
        BFVOID close (BFVOID);

        // Return whether or not a BFGTL Camera Device has been opened or not.
        BFBOOL isOpen (BFVOID) const;

        // Inverse of isOpen.
        bool operator! (BFVOID) const;

        // Equivalent to isOpen.
        operator bool (BFVOID) const;
        
        // Return the opened board handle. If opened by board number or switch connector, this
        // is an internally allocated handle. If opened by Bd handle, this is the externally
        // supplied handle. If closed, returns nullptr.
        Bd getBoardHandle (BFVOID) const;

        // Return the opened board number. Returns ~BFU32(0), if the board isn't open, or wasn't
        // opened with a board number (see getBoardSWConnector).
        BFU32 getBoardNumber (BFVOID) const;
    
        // Retrieve the opened board switch and connector. Retrieves ~BFU32(0), if the board isn't
        // open, or wasn't opened with openSWConnector (see getBoardNumber).
        BFVOID getBoardSWConnector (BFU32 &Switch, BFU32 &Connector) const;

        // Retrieve a list of all available Camera Device node names.
        std::vector<std::string> getNodeNames (BFVOID) const;

        // Iteratively retrieve the list of available Camera Device node names.
        BFBOOL enumerateNodeName (const BFSIZET index, BFCHAR *const nameBuf, BFSIZET *const pNameSize) const;

        // Retrieve a Camera Device node from a given node name.
        BaseNode getNode (std::string const& name) const;
        BaseNode getNode (const BFCHAR *const name) const;

    private:
        struct PrivateData;
        PrivateData *m_pd;

        // Non-copyable.
        Device (Device const&);
        Device& operator= (Device const&);
    };

    // NodeType codes.
    enum class NodeType
    {
        Unknown = BFGTL_TYPE_UNKNOWN,
        
        Value = BFGTL_NODE_TYPE_VALUE,
        Base = BFGTL_NODE_TYPE_BASE,
        Integer = BFGTL_NODE_TYPE_INTEGER,
        Boolean = BFGTL_NODE_TYPE_BOOLEAN,
        Command = BFGTL_NODE_TYPE_COMMAND,
        Float = BFGTL_NODE_TYPE_FLOAT,
        String = BFGTL_NODE_TYPE_STRING,
        Register = BFGTL_NODE_TYPE_REGISTER,
        Category = BFGTL_NODE_TYPE_CATEGORY,
        Enumeration = BFGTL_NODE_TYPE_ENUMERATION,
        EnumEntry = BFGTL_NODE_TYPE_ENUM_ENTRY,
        Port = BFGTL_NODE_TYPE_PORT,
    };

    // Node accessibility codes.
    enum class Access
    {
        Unknown = BFGTL_ACCESS_UNKNOWN,

        NI = BFGTL_ACCESS_NI,    // Not Implemented
        NA = BFGTL_ACCESS_NA,    // Not Accessible
        RO = BFGTL_ACCESS_RO,    // Read Only
        WO = BFGTL_ACCESS_WO,    // Write Only
        RW = BFGTL_ACCESS_RW,    // Read/Write
    };
    
    // The base class of all node types.
    struct BFDLL BaseNode
    {
    private:
        // Private constructor for our friend, Device::getNode.
        BaseNode (Bd hBoard, Device const& device, const BFGTLNode node);
        BaseNode friend ::BFGTLUtilities::Device::getNode (std::string const& name) const;
        BaseNode friend ::BFGTLUtilities::Device::getNode (const BFCHAR *const name) const;

    public:
        static const NodeType Type = NodeType::Base;

        // Constructors.
        BaseNode (BFVOID);

        BaseNode (BaseNode const& to_alias);
        BaseNode (BaseNode &&to_take);

        // Destructor.
        virtual ~BaseNode (BFVOID);
        
        // Copy methods.
        BaseNode& operator= (BaseNode const& to_alias);
        BaseNode& operator= (BaseNode &&to_take);

        // This instance represents a node.
        bool isValid (BFVOID) const;
        operator bool (BFVOID) const;

        // This instance is null.
        bool isNull (BFVOID) const;
        bool operator! (BFVOID) const;

        // Determine if this node is equivalent to a different node. Null instances
        // are not considered equivalent.
        bool operator== (BaseNode const& other) const;
        bool operator!= (BaseNode const& other) const;

        // Retrieve the node name.
        std::string name (BFVOID) const;
        bool getName (BFCHAR *const hBuf, BFSIZET *const pSize) const;

        // Retrieve the node display name.
        std::string displayName (BFVOID) const;
        bool getDisplayName (BFCHAR *const hBuf, BFSIZET *const pSize) const;
        
        // Retrieve the node tool-tip.
        std::string toolTip (BFVOID) const;
        bool getToolTip (BFCHAR *const hBuf, BFSIZET *const pSize) const;

        // Retrieve the node description.
        std::string description (BFVOID) const;
        bool getDescription (BFCHAR *const hBuf, BFSIZET *const pSize) const;
        
        // Retrieve the node type.
        NodeType type (BFVOID) const;
        
        // Retrieve the node accessibility.
        Access access (BFVOID) const;

        // Whether or not to ignore any cached data.
        bool ignoreCache (BFVOID) const;
        BFVOID setIgnoreCache (const bool ignore);

    protected:
        virtual void copy (BaseNode const& to_alias);
        virtual void copy (BaseNode &&to_take);

        struct PrivateData;
        PrivateData *m_pd;
    };

    // Private implementation classes.
    namespace PRIVATE_IMP
    {
        template <class NodeT, NodeType NODE_TYPE>
        struct NodeImpT : public NodeT, public virtual BaseNode
        {
            static const NodeType Type = NODE_TYPE;

            inline static bool is_convertible (BaseNode const& other)
            {
                const NodeType ot = other.type();
                if (NodeType::Value == Type)
                    return NodeType::Unknown != ot && NodeType::Base != ot;
                else
                    return Type == ot;
            }

            // Constructors.
            NodeImpT (BFVOID) { }

            NodeImpT (NodeImpT const& to_alias)
                : BaseNode ( to_alias )
            { }
            NodeImpT (NodeImpT &&to_alias)
                : BaseNode ( std::move(to_alias) )
            { }

            NodeImpT (BaseNode const& to_alias)
                : BaseNode ( is_convertible(to_alias) ? to_alias : BaseNode() )
            { }
            NodeImpT (BaseNode &&to_take)
                : BaseNode ( std::move(is_convertible(to_take) ? to_take : BaseNode()) )
            { }

            NodeImpT& operator= (BaseNode const& to_alias)
            {
                copy(to_alias);
                return *this;
            }

            NodeImpT& operator= (BaseNode &&to_take)
            {
                copy( std::move(to_take) );
                return *this;
            }

        private:
            virtual void copy (BaseNode const& to_alias)
            {
                BaseNode::copy( is_convertible(to_alias) ? to_alias : BaseNode() );
            }
            virtual void copy (BaseNode &&to_take)
            {
                BaseNode::copy( std::move(is_convertible(to_take) ? to_take : BaseNode()) );
            }
        };

        // The base of all value node types.
        struct BFDLL ValueNodeBase : public virtual BaseNode
        {
            // Get the node value as a string.
            std::string toString (BFVOID) const;
            bool getToString (BFCHAR *const hBuf, BFSIZET *const pSize) const;

            // Set the node value from a string.
            BFVOID fromString (std::string const& strVal);
            BFVOID fromString (const BFCHAR *const strVal);
        };

        // Structure to get/set integer node values.
        struct BFDLL IntegerNodeBase : public ValueNodeBase
        {
            typedef BFS64 Value;

            // Convenience accessors.
            Value value (BFVOID) const;
            Value minimum (BFVOID) const;
            Value maximum (BFVOID) const;
            Value increment (BFVOID) const;
            
            // Convenience modifier.
            BFVOID setValue (const Value val);
        };

        // Structure to get/set boolean node values.
        struct BFDLL BooleanNodeBase : public ValueNodeBase
        {
            typedef bool Value;

            // Convenience accessors.
            Value value (BFVOID) const;
            
            // Convenience modifier.
            BFVOID setValue (const Value val);
        };

        // Structure to get/set command node values.
        struct BFDLL CommandNodeBase : public ValueNodeBase
        {
            // Convenience execution methods.
            BFVOID execute (BFVOID);
            BFVOID operator() (BFVOID);
        };

        // Structure to get/set floating-point node values.
        struct BFDLL FloatNodeBase : public ValueNodeBase
        {
            typedef BFDOUBLE Value;

            // Convenience accessors.
            Value value (BFVOID) const;
            Value minimum (BFVOID) const;
            Value maximum (BFVOID) const;
            Value increment (BFVOID) const;
            
            // Convenience modifier.
            BFVOID setValue (const Value val);
        };

        // Structure to get/set string node values.
        struct BFDLL StringNodeBase : public ValueNodeBase
        {
            typedef std::string Value;

            // Convenience accessors.
            Value value (BFVOID) const;
            bool getValue (BFCHAR *const hBuf, BFSIZET *const pSize) const;
            BFS64 max_length (BFVOID) const;
            
            // Convenience modifier.
            BFVOID setValue (Value const& val);
            BFVOID setValue (const BFCHAR *const val);
        };

        // Structure to get/set register node values.
        struct BFDLL RegisterNodeBase : public ValueNodeBase
        {
            typedef std::vector<BFU8> DataArray;

            // Convenience data accessor.
            BFS64 address (BFVOID) const;
            BFS64 length (BFVOID) const;
            DataArray data (BFVOID) const;
            void getData (BFU8 *const dataBuf, const BFSIZET bufLen) const;
            
            // Convenience modifier.
            BFVOID setData (DataArray const& val);
            BFVOID setData (const BFU8 *const dataBuf, const BFSIZET bufLen);
        };

        // Structure to get/set category node values.
        struct BFDLL CategoryNodeBase : public ValueNodeBase
        {
            typedef std::vector<std::string> FeatureNames;
            typedef BaseNode Feature;
            typedef std::vector<Feature> Features;

            // Convenience category features accessor.
            BFS64 featureCount (BFVOID) const;

            FeatureNames featureNames (BFVOID) const;
            bool enumerateFeatureName (const BFS64 index, BFCHAR *const hBuf, BFSIZET *const pSize) const;

            Features features (BFVOID) const;
            bool getFeature (const BFS64 index, Feature *const pFeature) const;
        };

        // Structure to get/set enumeration node values.

            // Forward declaration.
        struct EnumEntryNodeBase;

        struct BFDLL EnumerationNodeBase : public ValueNodeBase
        {
            typedef BFS64 Value;
            typedef std::vector<std::string> EntryStrings;
            typedef std::vector<Value> EntryValues;
            typedef NodeImpT<EnumEntryNodeBase,NodeType::EnumEntry> Entry;
            typedef std::vector<Entry> Entries;
            
            // Convenience accessors.
            Value entryValue (BFVOID) const;

            std::string entryName (BFVOID) const;
            bool getEntryName (BFCHAR *const hBuf, BFSIZET *const pSize) const;

            std::string entrySymbolic (BFVOID) const;
            bool getEntrySymbolic (BFCHAR *const hBuf, BFSIZET *const pSize) const;
        
            BFS64 entryCount (BFVOID) const;

            EntryValues entryValues (BFVOID) const;
            bool enumerateEntryValue (const BFS64 index, Value *const pVal) const;

            EntryStrings entryNames (BFVOID) const;
            bool enumerateEntryName (const BFS64 index, BFCHAR *const hBuf, BFSIZET *const pSize) const;

            EntryStrings entrySymbolics (BFVOID) const;
            bool enumerateEntrySymbolic (const BFS64 index, BFCHAR *const hBuf, BFSIZET *const pSize) const;

            Entry entry (BFVOID) const;

            Entries entries (BFVOID) const;
            bool enumerateEntry (const BFS64 index, Entry *const pEntry) const;

            // Convenience modifiers.
            BFVOID setEntryValue (const Value val);

            BFVOID setEntryName (std::string const& name);
            BFVOID setEntryName (const BFCHAR *const name);

            BFVOID setEntrySymbolic (std::string const& symbolic);
            BFVOID setEntrySymbolic (const BFCHAR *const symbolic);
        };

        // Structure to get/set enumeration entry node values.
        struct BFDLL EnumEntryNodeBase : public ValueNodeBase
        {
            // Convenience accessors.
            BFS64 value (BFVOID) const;

            std::string symbolic (BFVOID) const;
            bool getSymbolic (BFCHAR *const hBuf, BFSIZET *const pSize) const;
        };

        // Structure to get/set port node values.
        struct BFDLL PortNodeBase : public virtual BaseNode
        { };
    }

    // Typed node classes.
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::ValueNodeBase,NodeType::Value>
        ValueNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::IntegerNodeBase,NodeType::Integer>
        IntegerNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::BooleanNodeBase,NodeType::Boolean>
        BooleanNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::CommandNodeBase,NodeType::Command>
        CommandNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::FloatNodeBase,NodeType::Float>
        FloatNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::StringNodeBase,NodeType::String>
        StringNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::RegisterNodeBase,NodeType::Register>
        RegisterNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::CategoryNodeBase,NodeType::Category>
        CategoryNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::EnumerationNodeBase,NodeType::Enumeration>
        EnumerationNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::EnumEntryNodeBase,NodeType::EnumEntry>
        EnumEntryNode;
    typedef PRIVATE_IMP::NodeImpT<PRIVATE_IMP::PortNodeBase,NodeType::Port>
        PortNode;
}

#endif // INCLUDED__BITFLOW__B_F_G_T_L__UTILITIES__HPP
