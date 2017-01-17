#include "ClientState.h"

ClientState::ClientState() :
    m_authorizationState(Unauthorized),
    m_exerciseState(ExerciseStopped)
{
}

ClientState::AuthorizationState ClientState::authorizationState() const
{
    return m_authorizationState;
}

void ClientState::setAuthorizationState(const ClientState::AuthorizationState & authorizationState)
{
    m_authorizationState = authorizationState;
}

QString ClientState::username() const
{
    return m_username;
}

void ClientState::setUsername(const QString & username)
{
    m_username = username;
}

ClientState::ExerciseState ClientState::exerciseState() const
{
    return m_exerciseState;
}

void ClientState::setExerciseState(const ClientState::ExerciseState & exerciseState)
{
    m_exerciseState = exerciseState;
}

Exercise::Pointer ClientState::exercise() const
{
    return m_exercise;
}

void ClientState::setExercise(Exercise::Pointer exercise)
{
    m_exercise = exercise;
}

