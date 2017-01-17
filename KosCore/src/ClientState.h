#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <Exercise.h>
#include <QString>

class ClientState
{

public:

    enum AuthorizationState
    {
        Authorized = 0,
        AuthtorizeInProgress = 1,
        Unauthorized = 2,
        UnauthtorizeInProgress = 3
    };

    enum ExerciseState
    {
        ExerciseStopped = 0,
        ExerciseStopInProgress = 1,
        ExerciseStarted = 2,
        ExerciseStartInProgress = 3
    };

    ClientState();

    ClientState::AuthorizationState authorizationState() const;
    void setAuthorizationState(const ClientState::AuthorizationState & authorizationState);

    QString username() const;
    void setUsername(const QString & username);

    ClientState::ExerciseState exerciseState() const;
    void setExerciseState(const ClientState::ExerciseState & exerciseState);

    Exercise::Pointer exercise() const;
    void setExercise(Exercise::Pointer exercise);

private:

    AuthorizationState m_authorizationState;
    QString m_username;

    ExerciseState m_exerciseState;
    Exercise::Pointer m_exercise;

};

#endif // CLIENTSTATE_H
