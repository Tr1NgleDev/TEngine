#pragma once

#include <vector>
#include <functional>
#include <utility>

namespace TEngine
{
    template<class Sig>
    struct Action
	{
        Action() = default;

        template<typename Functor>
        int add(Functor&& f)
        {
            _funcs.emplace_back(std::forward<Functor>(f));
            _lastInd++;
            return _lastInd;
        }

        void remove(int ind)
    	{
            if (ind < 0 || ind >= _funcs.size()) return;

            _funcs[ind] = nullptr;
        }

        template<class... Args>
        void operator()(Args&&... args) const
    	{
            for (auto& f : _funcs)
                if(f != nullptr)
					f(args...);
        }

        Action(const Action<Sig>& other)
        {
            _lastInd = other._lastInd;
            _funcs = other._funcs;
        }

        Action(Action<Sig>&& other) noexcept
        {
            _lastInd = other._lastInd;
            _funcs = std::move(other._funcs);

            other._lastInd = -1;
            other._funcs.clear();
        }

        Action& operator=(const Action<Sig>& other)
        {
            if (this != &other)
            {
                _lastInd = other._lastInd;
                _funcs = other._funcs;
            }
            return *this;
        }

        Action& operator=(Action<Sig>&& other) noexcept
        {
            if (this != &other)
            {
                _lastInd = other._lastInd;
                _funcs = std::move(other._funcs);

                other._lastInd = -1;
                other._funcs.clear();
            }
            return *this;
        }

        void dispose()
        {
            _lastInd = -1;
	        _funcs.clear();
        }

    private:
        int _lastInd = -1;
        std::vector<std::function<Sig>> _funcs;
	};
}