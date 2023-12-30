//
// Created by tibov on 22/12/23.
//

#include "WorldReader.h"
#include "iostream"
namespace Logic::WorldLoading {


    WorldReader::WorldReader(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score>& score) : WorldLoader(std::move(factory), score) {

    }
} // Logic::WorldLoading