#include <gtest/gtest.h>
#include "Model/reservoir/grid/xyzcoordinate.h"
#include "Model/properties/property.h"
#include "Model/properties/binary_property.h"
#include "Model/properties/discrete_property.h"
#include "Model/properties/continous_property.h"
#include "Model/properties/variable_property_container.h"

using namespace Model::Properties;

namespace {

class VariableContainerTest : public ::testing::Test {
protected:
    VariableContainerTest () {
        variable_container_ = new VariablePropertyContainer();
    }
    virtual ~VariableContainerTest () { }

    virtual void SetUp() {
        variable_container_->AddVariable(continous_properties_[0]);
        variable_container_->AddVariable(continous_properties_[1]);
        variable_container_->AddVariable(continous_properties_[2]);
        variable_container_->AddVariable(discrete_properties_[0]);
        variable_container_->AddVariable(binary_properties_[0]);
        variable_container_->AddVariable(binary_properties_[1]);
    }

    VariablePropertyContainer *variable_container_;
    QList<ContinousProperty *> continous_properties_ {
        new ContinousProperty(2.0),
        new ContinousProperty(5.0),
        new ContinousProperty(1.0)
    };
    QList<DiscreteProperty *> discrete_properties_ {
        new DiscreteProperty(5)
    };
    QList<BinaryProperty *> binary_properties_ {
        new BinaryProperty(false),
        new BinaryProperty(true)
    };
};

TEST_F(VariableContainerTest, Constructor) {
    // If the lists exist, the constructor has been run
    EXPECT_EQ(variable_container_->BinaryVariableSize(), 2);
    EXPECT_EQ(variable_container_->DiscreteVariableSize(), 1);
    EXPECT_EQ(variable_container_->ContinousVariableSize(), 3);
}

TEST_F(VariableContainerTest, Retrieval) {
    EXPECT_EQ(variable_container_->GetBinaryVariable(binary_properties_[0]->id())->value(), false);
    EXPECT_EQ(variable_container_->GetDiscreteVariable(discrete_properties_[0]->id())->value(), 5);
    EXPECT_FLOAT_EQ(variable_container_->GetContinousVariable(continous_properties_[2]->id())->value(), 1.0);
    EXPECT_EQ(variable_container_->GetBinaryVariableValues()[binary_properties_[0]->id()], false);
    EXPECT_EQ(variable_container_->GetDiscreteVariableValues()[discrete_properties_[0]->id()], 5);
    EXPECT_FLOAT_EQ(variable_container_->GetContinousVariableValues()[continous_properties_[2]->id()], 1.0);
    EXPECT_THROW(variable_container_->GetContinousVariable(QUuid::createUuid()), VariableIdDoesNotExistException);
    EXPECT_THROW(variable_container_->GetBinaryVariable(QUuid::createUuid()), VariableIdDoesNotExistException);
    EXPECT_THROW(variable_container_->GetDiscreteVariable(QUuid::createUuid()), VariableIdDoesNotExistException);
}

TEST_F(VariableContainerTest, Deletion) {
    EXPECT_NO_THROW(variable_container_->DeleteBinaryVariable(binary_properties_[0]->id()));
    EXPECT_THROW(variable_container_->GetBinaryVariable(0), VariableIdDoesNotExistException);
    EXPECT_THROW(variable_container_->DeleteDiscreteVariable(QUuid::createUuid()), VariableIdDoesNotExistException);
    EXPECT_NO_THROW(variable_container_->DeleteDiscreteVariable(discrete_properties_[0]->id()));
    EXPECT_EQ(variable_container_->DiscreteVariableSize(), 0);
    EXPECT_NO_THROW(variable_container_->DeleteContinousVariable(continous_properties_[1]->id()));
    EXPECT_THROW(variable_container_->GetContinousVariable(continous_properties_[1]->id()), VariableIdDoesNotExistException);
    EXPECT_DOUBLE_EQ(variable_container_->GetContinousVariable(continous_properties_[2]->id())->value(), 1.0);
}

}
