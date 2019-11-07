//
// Created by Rui Pinto on 10/11/2019.
//

#include "IndividualStatistics.h"

IndividualStatistics::IndividualStatistics(unsigned int id, unsigned int soccerPlayerID, unsigned int gameID, unsigned short goals,
        unsigned short assists, unsigned short passes, unsigned short shots, unsigned short shotsTarget,
        unsigned short travelledDistance, unsigned short playedMinutes, unsigned short yellowCards, unsigned short redCards,
        unsigned short fouls, bool injured) {

    this->id = id;
    this->soccerPlayerID = soccerPlayerID;
    this->goals = goals;
    this->assists = assists;
    this->passes = passes;
    this->shots = shots;
    this->shotsTarget = shotsTarget;
    this->travelledDistance = travelledDistance;
    this->playedMinutes = playedMinutes;
    this->yellowCards = yellowCards;
    this->redCards = redCards;
    this->fouls = fouls;
    this->injured = injured;
}

unsigned int IndividualStatistics::getId() const {
    return id;
}

unsigned int IndividualStatistics::getSoccerPlayerID() const {
    return soccerPlayerID;
}

unsigned int IndividualStatistics::getGameID() const {
    return gameID;
}

unsigned short IndividualStatistics::getGoals() const {
    return goals;
}

unsigned short IndividualStatistics::getAssists() const {
    return assists;
}

unsigned short IndividualStatistics::getPasses() const {
    return passes;
}

unsigned short IndividualStatistics::getShots() const {
    return shots;
}

unsigned IndividualStatistics::getShotsTarget() const {
    return shotsTarget;
}

unsigned short IndividualStatistics::getTravelledDistance() const {
    return travelledDistance;
}

unsigned short IndividualStatistics::getPlayedMinutes() const {
    return playedMinutes;
}

unsigned short IndividualStatistics::getYellowCards() const {
    return yellowCards;
}

unsigned short IndividualStatistics::getRedCards() const {
    return redCards;
}

unsigned short IndividualStatistics::getFouls() const {
    return fouls;
}

bool IndividualStatistics::getInjured() const {
    return injured;
}


void IndividualStatistics::setSoccerPlayerID(unsigned int soccerPlayerID) {
    this->soccerPlayerID = soccerPlayerID;
}

void IndividualStatistics::setGameID(unsigned int gameID) {
    this->gameID = gameID;
}

void IndividualStatistics::setGoals(unsigned short goals) {
    this->goals = goals;
}

void IndividualStatistics::setAssists(unsigned short assists) {
    this->assists = assists;
}

void IndividualStatistics::setPasses(unsigned short passes) {
    this->passes = passes;
}

void IndividualStatistics::setShots(unsigned short shots) {
    this->shots = shots;
}

void IndividualStatistics::setShotsTarget(unsigned short shotsTarget) {
    this->shotsTarget = shotsTarget;
}

void IndividualStatistics::setTravelledDistance(unsigned short travelledDistance) {
    this->travelledDistance = travelledDistance;
}

void IndividualStatistics::setPlayedMinutes(unsigned short playedMinutes) {
    this->playedMinutes = playedMinutes;
}

void IndividualStatistics::setYellowCards(unsigned short yellowCards) {
    this->yellowCards = yellowCards;
}

void IndividualStatistics::setRedCards(unsigned short redCards) {
    this->redCards = redCards;
}

void IndividualStatistics::setFouls(unsigned short fouls) {
    this->fouls = fouls;
}

void IndividualStatistics::setInjured(bool injured) {
    this->injured = injured;
}

